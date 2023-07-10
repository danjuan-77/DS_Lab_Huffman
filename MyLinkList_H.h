#ifndef MYLINKLIST_H
#define MYLINKLIST_H

#define OK true
#define ERROR false

typedef bool Status;

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

#endif