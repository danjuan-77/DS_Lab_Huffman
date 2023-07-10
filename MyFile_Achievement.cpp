#include "MyFile_H.h"
#include <iostream>
using namespace std;

/*读取源文件信息,统计字符出现频率*/
Status LoadSourseText()
{
    FILE *fp1 = fopen("temp\\TestTextSource.txt", "r");
    int chars[256] = {0}; // 256位ASCII码表
    int textLength = 0;   // 统计文本长度
    int charNumber = 0;   // 统计字符类型个数
    char c;

    if (fp1 == NULL)
    {
        cout << "文件打开失败!!!" << endl;
        return ERROR;
    }

    // 统计字符频率及字符串长度
    while ((c = fgetc(fp1)) != EOF)
    {
        chars[c]++;
        textLength++;
    }

    // 统计字符串中有多少种不同字符
    for (int i = 0; i < 256; i++)
    {
        if (chars[i] != 0)
            charNumber++;
    }

    fclose(fp1);

    // 将信息写入temp\CharFrequency.txt中
    FILE *fp2 = fopen("temp\\CharFrequency.txt", "w+");
    fprintf(fp2, "%d\t%d", textLength, charNumber);
    for (int i = 0; i < 256; i++)
    {
        if (chars[i] != 0)
        {
            fprintf(fp2, "\n%d %d", i, chars[i]);
        }
    }
    fclose(fp2);
    cout << "文本文件加载完毕!!!" << endl;
    // 终端显示结果
    int col = 0;
    printf("文本长度:%d    字符种类:%d\n", textLength, charNumber);
    printf("按照ASCII码排列,字符出现频率如下:\n");
    for (int i = 0; i < 256; i++)
    {
        if (chars[i] != 0)
        {
            if (i == 32)
            {
                printf("SP:%d\t\t", chars[i]); // 空格
            }
            else if (i == 13)
            {
                printf("EN:%d\t\t", chars[i]); // 回车
            }
            else if (i == 10)
            {
                printf("NL:%d\t\t", chars[i]); // 换行
            }
            else
            {
                printf("%c:%d\t\t", i, chars[i]);
            }
            col++;
            if (col % 5 == 0) // 一行显示5个
            {
                printf("\n");
            }
        }
    }
    cout << endl;
    cout << "字符集统计完毕!!!信息保存在temp\\CharFrequency.txt中" << endl;
    return OK;
}

/*读取temp\CharFrequency.txt中的信息*/
Status LoadChar(LinkList &L, int &textLength, int &charNumber)
{
    ElemType e;
    ListInit(L);                                      // 初始化线性表
    FILE *fp = fopen("temp\\CharFrequency.txt", "r"); // 打开文件

    fscanf(fp, "%d\t%d", &textLength, &charNumber); // 读出文本长度和字符个数信息

    for (int i = 1; i <= charNumber; i++)
    {
        fscanf(fp, "\n%d %d", &e.ASCII_CODE, &e.weight); // 读出字符的ASCCII码和次数
        ListInsert(L, i, e);                             // 插入到线性表中
    }
    fclose(fp);
    cout<<"字符集信息获取完毕!!!"<<endl;
    return OK;
}

/*计算正确率*/
Status CalculateAccuracy(int n)
{
    int i;
    char ch1, ch2;
    float textLength = float(n), cnt = 0.0, accuracy = 0.0;
    FILE *source = fopen("temp\\TestTextSource.txt", "r");
    FILE *decode = fopen("temp\\HuffmanDecoded.txt", "r");

    for (i = 0; i <= textLength; i++)
    {
        ch1 = fgetc(source);
        ch2 = fgetc(decode);
        if (ch1 != ch2)
        {
            cnt++;
        }
    }
    accuracy = (textLength - cnt) / textLength;
    printf("源文件与译码文件相比,错误个数为:%d,准确率为:%.2f%%\n",
           (int)cnt, accuracy * 100);
    return OK;
}

/*计算文件的压缩率*/
Status CalculateCompressionRate()
{
    long textSize, decodedSize;
    float compressionRate;
    FILE *source = fopen("temp\\TestTextSource.txt", "r");
    FILE *decode = fopen("temp\\HuffmanEncodedToHuf.huf ", "r");
    // 获取文件TestTextSource.txt的大小
    fseek(source, 0L, SEEK_END);
    textSize = ftell(source);
    // 获取文件HuffmanEncodedToHuf.huf 的大小
    fseek(decode, 0L, SEEK_END);
    decodedSize = ftell(decode);
    compressionRate = (float)decodedSize / (float)textSize;
    printf("源文件大小为:%d字节  压缩后大小为:%d字节\n压缩率为:%.2f%%\n", textSize, decodedSize, compressionRate * 100.0);
    return OK;
}