> temp文件夹存放.txt和.huf文件，用于编码，译码，压缩，解压
>
> temp文件夹中的文件说明

1. 测试用的文本文件 `TestTextSource.txt`
2. 存放字符以及对应的出现次数 `CharFrequency.txt`
3. 存放字符以及对应的哈夫曼编码 `HuffmanCodeInfo.txt`
4. 存放.txt文件进行哈夫曼编码之后的文件 `HuffmanEncoded.txt`
5. 存放转换成.huf压缩文件的过渡文件 `TempHuf.txt`
6. 对`HuffmanEncoded.txt`进行压缩得到的文件 `HuffmanEncodedToHuf.huf `
7. `HuffmanEncodedToHuf.huf`解压缩得到的文件 `HufToHuffmanEncoded.txt`
8. 对`HufToHuffmanEncoded.txt`进行解码得到的字符文件` HuffmanDecoded.txt`

修改`TestTextSource.txt`中的文件内容，实现对不同的内容进行压缩，压缩成`HuffmanEncodedToHuf.huf`

**通过编码——压缩——解压——译码来模拟通信**

**主程序**是`Huffman_Main.cpp`

---

自定义头文件：

* `MyFile_H.h`用于打开文本文件和压缩文件，进行文件比较，计算压缩率和正确率
  * 对应的实现文件`MyFile_Achievement.cpp`

* `MyLinkList_H.h`自定义的线性表，自定义数据类型和操作
  * 对应的实现文件`MyLinkList_Achievement.cpp`
* `MyHuffman_H.h`自定义HuffmanTree中的结点数据类型，自定义建树、编码、解码、压缩、解压操作等
  * 对应的实现文件`MyHuffman_Achievement.cpp`

---

基本类型定义：

```cpp
#define OK true
#define ERROR false
typedef bool Status;
```

---

MyLinkList_H.h

```cpp
// 链表数据域元素类型的定义
typedef struct
{
    int ASCII_CODE;            // 存ASSCII码
    int weight;                // 存频率
    char *HuffmanCode;         // HuffmanCode所在数组的指针
    int HuffmanCodeLength = 0; // HuffmanCode数组的长度

} ElemType;

// 链表的定义
typedef struct Node
{
    ElemType elem;     // 数据域
    struct Node *next; // next指针域
} LinkNode, *LinkList;

// 链表的初始化
Status ListInit(LinkList &L);

// 链表的元素插入
Status ListInsert(LinkList &L, int i, ElemType e);

// 链表的整表删除
Status ListDestroy(LinkList &L);

// 链表的遍历操作
Status TraverseList(LinkList L);
```

---

MyFile_H.h

```cpp
/*读取源文件信息，统计字符出现频率*/
Status LoadSourseText();

/*读取CodeFrequency.txt中的信息*/
Status LoadChar(LinkList &L, int &textLength, int &charNumber);

/*计算正确率*/
Status CalculateAccuracy(int n);

/*计算压缩率*/
Status CalculateCompressionRate();
```

---

MyHuffman_H.h

```cpp
/*Huffman树结点类型定义*/
typedef struct
{
    unsigned int weight;                  // 结点权重
    unsigned int ASCII_CODE;            // 结点对应的ASSCII码
    unsigned int parent, lchild, rchild; // 双亲，左子树，右子树
} HTNode, *HuffmanTree;

/*选择权值最小的两个节点*/
Status HuffmanTreeSelect(HuffmanTree HT, int n, int &s1, int &s2);

/*创建Huffman树*/
Status HuffmanTreeCreate(HuffmanTree &HT, int n, LinkList L);

/*打印Huffman树*/
Status HuffmanTreePrint(HuffmanTree HT, int n);

/*从叶子到根逆向求每个字符的Huffman编码*/
Status HuffmanCodeCreate(HuffmanTree HT, int n, LinkList &L);

/*存储Huffman编码进文件中*/
Status HuffmanCodeWrite(HuffmanTree HT, int n, LinkList &L);

/*对文件进行Huffman编码存放到temp\HuffmanEncoded.txt*/
Status HuffmanCodeEncode(HuffmanTree HT, LinkList L);

/*生成.huf文件*/
Status CompressionToHuf();

/*解压.huf文件*/
Status DecompressionFromHuf();

/*对文件进行Huffman解码生成HuffmanDecoded.txt*/
Status HuffmanCodeDecode(HuffmanTree HT, int charNumber, int textLength);

/*返回某个字符的Huffman编码所在的指针*/
char *HuffmanCodePtr(LinkList L, char c);

/*每8位转化为对应的ASCII码*/
char ByteToAscii(int n[]);
```