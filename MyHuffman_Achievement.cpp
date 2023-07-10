#include "MyHuffman_H.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

/*选择权值最小的两个节点*/
Status HuffmanTreeSelect(HuffmanTree HT, int n, int &s1, int &s2)
{
    // HT表示HuffmanTree的数组，n表示HT数组的长度
    // 将最小的两个结点的下标通过s1,s2返回
    // 前2个循环，先找到HT数组中weight最小的一个结点
    // 后2个循环，找到HT数组中weight第二小的结点
    for (int i = 1; i <= n; i++)
    {
        if (HT[i].parent == 0) // 先找到一个根结点去初始化s1
        {
            s1 = i;
            break;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        // 当前结点i比s1结点的weight还要小，且i结点必须是根结点，则更新s1
        if (HT[i].weight < HT[s1].weight && HT[i].parent == 0)
        {
            s1 = i;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        // 找到一个根结点去初始化s2，这个结点不能是刚刚找到的s1
        if (HT[i].parent == 0 && i != s1)
        {
            s2 = i;
            break;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        // 当前结点i比结点s2的weight还要小，且i结点是根结点，且i结点不能是s1，更新s2
        if (HT[i].weight < HT[s2].weight && i != s1 && HT[i].parent == 0)
        {
            s2 = i;
        }
    }
    return OK;
}

/*创建Huffman树*/
Status HuffmanTreeCreate(HuffmanTree &HT, int n, LinkList L)
{
    if (n <= 1)
        return ERROR;
    int m = n * 2 - 1;
    LinkList p = L->next;
    HT = new HTNode[m + 1];
    // 树的初始化
    for (int i = 1; i < m + 1; i++)
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    // 获取结点的weight和ASCII码
    for (int i = 1; i <= n; i++)
    {
        HT[i].weight = p->elem.weight;
        HT[i].ASCII_CODE = p->elem.ASCII_CODE;
        p = p->next;
    }
    // 开始建树
    int s1, s2;
    for (int i = n + 1; i <= m; i++)
    {
        HuffmanTreeSelect(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    cout << "Huffman树构建完毕!!!" << endl;
    return OK;
}

/*打印Huffman树*/
Status HuffmanTreePrint(HuffmanTree HT, int n)
{
    // printf("Huffman树的信息如下:\n");
    cout << "Huffman树的信息如下:" << endl;
    // printf("结点\t字符\t权值\t双亲\t左孩子\t右孩子\t\n");
    cout << "结点\t字符\t权值\t双亲\t左孩子\t右孩子\t" << endl;
    for (int i = 1; i <= n * 2 - 1; i++)
    {
        if (HT[i].ASCII_CODE == 32)
        {
            printf("%d\t空格\t%d\t%d\t%d\t%d\t\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
        }
        else if (HT[i].ASCII_CODE == 13)
        {
            printf("%d\t回车\t%d\t%d\t%d\t%d\t\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
        }
        else if (HT[i].ASCII_CODE == 10)
        {
            printf("%d\t换行\t%d\t%d\t%d\t%d\t\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
        }
        else if (HT[i].lchild != 0 || HT[i].rchild != 0)
        {
            printf("%d\t无\t%d\t%d\t%d\t%d\t\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
        }
        else
        {
            printf("%d\t%c\t%d\t%d\t%d\t%d\t\n", i, HT[i].ASCII_CODE, HT[i].weight, HT[i].parent, HT[i].lchild,
                   HT[i].rchild);
        }
    }
    cout << "Huffman树打印完毕!!!" << endl;
    return OK;
}

/*从叶子到根逆向求每个字符的Huffman编码*/
Status HuffmanCodeCreate(HuffmanTree HT, int n, LinkList &L)
{
    char *cd = new char[n]; // 临时字符串cd
    LinkList p = L->next;
    cd[n - 1] = '\0'; // cd的最后一个位置是结束字符
    for (int i = 1; i <= n; i++)
    {
        int start = n - 1;
        int f = HT[i].parent;
        int c = i;
        while (f != 0)
        {
            if (HT[f].lchild == c)
            {
                cd[--start] = '0';
            }
            else
            {
                cd[--start] = '1';
            }
            c = f;
            f = HT[f].parent;
        }
        p->elem.HuffmanCode = new char[n - start];
        strcpy(p->elem.HuffmanCode, &cd[start]);
        p->elem.HuffmanCodeLength = n - start - 1;
        p = p->next;
    }
    delete cd;
    cout << "字符的Huffman编码构建完毕!!!" << endl;
    return OK;
}

/*存储Huffman编码进文件中*/
Status HuffmanCodeWrite(HuffmanTree HT, int n, LinkList &L)
{
    LinkList p = L->next;
    FILE *fp = fopen("temp\\HuffmanCodeInfo.txt", "w+");
    cout << "各字符对应的Huffman编码为:" << endl;
    fprintf(fp, "char number:%d\n", n);
    int col = 0;
    for (int i = 1; i <= n; i++)
    {
        fprintf(fp, "%d\t%d\t%d\t", p->elem.ASCII_CODE, p->elem.weight, p->elem.HuffmanCodeLength);
        if (p->elem.ASCII_CODE == 32)
        {
            cout << setiosflags(ios::left) << setw(5) << "SP"
                 << ": ";
        }
        else if (p->elem.ASCII_CODE == 13)
        {
            cout << setiosflags(ios::left) << setw(5) << "EN"
                 << ": ";
        }
        else if (p->elem.ASCII_CODE == 10)
        {
            cout << setiosflags(ios::left) << setw(5) << "NL"
                 << ": ";
        }
        else
        {
            cout << setiosflags(ios::left) << setw(5) << char(p->elem.ASCII_CODE) << ": ";
        }
        cout << setiosflags(ios::left) << setw(20) << p->elem.HuffmanCode;
        p->elem.HuffmanCode = &p->elem.HuffmanCode[0];
        while (*p->elem.HuffmanCode != '\0')
        {
            fprintf(fp, "%c", *p->elem.HuffmanCode);
            p->elem.HuffmanCode++;
        }
        col++;
        fprintf(fp, "\n");
        if (col % 4 == 0)
        {
            printf("\n");
        }
        p = p->next;
    }
    cout << "\n文件写入完毕!!!信息保存在temp\\HuffmanCodeInfo.txt中" << endl;
    fclose(fp);
    ListDestroy(L);
    return OK;
}

/*对文件进行Huffman编码存放到temp\HuffmanEncoded.txt*/
Status HuffmanCodeEncode(HuffmanTree HT, LinkList L)
{
    FILE *fp = fopen("temp\\HuffmanCodeInfo.txt", "r"); // 打开字符-编码文件
    int charNumber = 0;
    ElemType e;
    ListInit(L);
    fscanf(fp, "char number:%d\n", &charNumber);
    for (int i = 1; i <= charNumber; i++)
    {
        fscanf(fp, "%d\t%d\t%d\t", &e.ASCII_CODE, &e.weight, &e.HuffmanCodeLength);
        e.HuffmanCode = new char[e.HuffmanCodeLength];
        fscanf(fp, "%s\n", e.HuffmanCode);
        ListInsert(L, i, e);
    }
    char c, *ch;
    FILE *sourcefile = fopen("temp\\TestTextSource.txt", "r");
    FILE *huffmanEncoded = fopen("temp\\HuffmanEncoded.txt", "w+");
    while (!feof(sourcefile))
    {
        c = fgetc(sourcefile);
        ch = HuffmanCodePtr(L, c);
        // 写入Huffman 0/1编码
        while (*ch != '\0')
        {
            printf("%c", *ch);
            fputc(*ch, huffmanEncoded);
            ch++;
        }
    }
    cout << "\nHuffman编码完毕!\n信息保存在temp\\HuffmanEncoded.txt" << endl;
    fclose(fp);
    fclose(sourcefile);
    fclose(huffmanEncoded);
    ListDestroy(L);
    return OK;
}

/*生成.huf文件*/
Status CompressionToHuf()
{
    FILE *fp = fopen("temp\\HuffmanEncoded.txt", "r"); // 打开编码后的文件
    FILE *temp = fopen("temp\\TempHuf.txt", "wb+");
    FILE *huf = fopen("temp\\HuffmanEncodedToHuf.huf", "wb+");
    int code[8] = {0};  // 存放8bit01信息
    int codeNumber = 0; // 统计01个数
    char c;
    while (!feof(fp))
    {
        if (c = fgetc(fp) == '\n')
        {
            break;
        }
        codeNumber++;
    }
    // 计算需要补1的个数
    int codeComplement = codeNumber % 8;
    fseek(fp, 0L, SEEK_SET);
    for (int i = 1; i <= codeNumber; i++)
    {
        c = fgetc(fp);
        fputc(c, temp);
    }
    // 对文件进行补1，使得总长度为8的整数倍
    if (codeComplement != 0)
    {
        for (int i = 1; i <= 8 - codeComplement; i++)
        {
            fprintf(temp, "%d", 1);
        }
    }
    fseek(temp, 0L, SEEK_SET);
    fputc(8 - codeComplement, huf); // 在开头告知补1个数
    // 对文件进行编码
    for (int i = 1, j = -1; i <= (codeComplement == 0 ? codeNumber : codeNumber + 8 - codeComplement); i++)
    {
        c = fgetc(temp);
        if (c == '1')
        {
            code[++j] = 1;
        }
        else
        {
            code[++j] = 0;
        }
        if (j == 7)
        {
            c = ByteToAscii(code);
            fputc(c, huf);
            for (int t = 0; t < 8; t++)
            {
                code[t] = 0;
            }
            j = -1;
        }
    }

    cout << "压缩完毕!!!信息保存在temp\\HuffmanEncodedToHuf.huf中" << endl;
    fclose(fp);
    fclose(temp);
    fclose(huf);
    return OK;
}

/*解压.huf文件*/
Status DecompressionFromHuf()
{

    FILE *huf = fopen("temp\\HuffmanEncodedToHuf.huf", "rb");
    FILE *unzip = fopen("temp\\HufToHuffmanEncoded.txt", "wb+");
    long huflength = 0;
    double code_mod = 0.0;
    char c;
    long count = 0;
    // 获取文件长度
    fseek(huf, 0L, SEEK_SET);
    fseek(huf, 0L, SEEK_END);
    huflength = ftell(huf);
    // 重新定位文件指针，开始读取
    fseek(huf, 0L, SEEK_SET);
    c = fgetc(huf);
    // 解码的时候获取huf文件的第一个字符，计算得到补1的个数
    for (int i = 0; i <= 7; i++) // 4还是7?
    {
        code_mod += ((c >> i) & 1) * pow(2, i);
    }
    // 对huf文件进行译码
    while (!feof(huf))
    {
        c = fgetc(huf);
        for (int t = 0; t < 8; t++)
        {
            if (((c >> (7 - t)) & 1) == 1)
            {
                count++;
                fputc(49, unzip); // set 1
                if (count == (8 * (huflength - 1) - code_mod))
                {
                    break;
                }
            }
            else if (((c >> (7 - t)) & 1) == 0)
            {
                count++;
                fputc(48, unzip); // set 0
                if (count == (8 * (huflength - 1) - code_mod))
                {
                    break;
                }
            }
        }
        if (count == (8 * (huflength - 1) - code_mod))
        {
            break;
        }
    }
    cout << "解压完毕!!!信息保存在temp\\HufToHuffmanEncoded.txt中" << endl;
    fclose(huf);
    fclose(unzip);
    return OK;
}

/*对文件进行Huffman解码生成HuffmanDecoded.txt*/
Status HuffmanCodeDecode(HuffmanTree HT, int charNumber, int textLength)
{
    FILE *encodefile = fopen("temp\\HufToHuffmanEncoded.txt", "r");
    // FILE *encodefile = fopen("temp\\HuffmanEncoded.txt", "r");// test
    FILE *decodefile = fopen("temp\\HuffmanDecoded.txt", "w+");
    int m = 2 * charNumber - 1;
    int cnt = 0; // 统计译码个数
    char c;
    // 从根开始，依次寻找Huffman编码对应的字符
    while (!feof(encodefile))
    {
        c = fgetc(encodefile);
        if (cnt == textLength)
        {
            break;
        }
        if (c == '0')
        {
            m = HT[m].lchild;
        }
        else if (c == '1')
        {
            m = HT[m].rchild;
        }
        if (HT[m].lchild == 0 && HT[m].rchild == 0)
        {
            fputc(HT[m].ASCII_CODE, decodefile);
            m = 2 * charNumber - 1;
            cnt++;
        }
    }
    cout << "译码完毕!!!信息保存在temp\\HuffmanDecoded.txt中!" << endl;
    fclose(encodefile);
    fclose(decodefile);
    return OK;
}

/*每8位转化为对应的ASCII码*/
char ByteToAscii(int n[])
{
    char res = 0;
    for (int i = 0; i < 8; i++)
    {
        // 三目运算对一个byte进行移位操作
        n[i] == 1 ? (res |= (1 << 7 - i)) : (res &= ~(1 << (7 - i)));
    }
    return res;
}

/*返回某个字符的Huffman编码所在的指针*/
char *HuffmanCodePtr(LinkList L, char c)
{
    LinkList p = L->next;
    while (p->next && p->elem.ASCII_CODE != c)
    {
        p = p->next;
    }
    return p->elem.HuffmanCode;
}