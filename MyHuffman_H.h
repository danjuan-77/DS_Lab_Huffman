#ifndef MYHUFFMAN_H
#define MYHUFFMAN_H
#include "MyLinkList_H.h"

#define OK true
#define ERROR false

typedef struct
{
    unsigned int weight;                 // 结点权重
    unsigned int ASCII_CODE;             // 结点对应的ASSCII码
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

#endif