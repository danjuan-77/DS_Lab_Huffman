#include <stdlib.h>
#include <malloc.h>
#include "MyLinkList_H.h"
#include <iostream>
#include <iomanip>
using namespace std;

// 链表的初始化
Status ListInit(LinkList &L)
{
    L = new LinkNode;
    L->next = NULL;
    return OK;
}

// 链表的元素插入
Status ListInsert(LinkList &L, int i, ElemType e)
{
    LinkList p = L;
    int j = 0;
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (j > i - 1 || p == NULL)
        return ERROR;
    LinkList s = new LinkNode;
    s->elem = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

// 链表的整表删除
Status ListDestroy(LinkList &L)
{
    LinkList p;
    while (L)
    {
        p = L;
        L = p->next;
        delete p;
    }
    return OK;
}

// 链表的遍历操作
Status TraverseList(LinkList L)
{

    LinkList p = L->next;
    cout << setiosflags(ios::left) << setw(5) << "ASCII"
         << ": " << setiosflags(ios::left) << setw(5) << "Weight" << endl;

    while (p)
    {
        cout << setiosflags(ios::left) << setw(5) << p->elem.ASCII_CODE << ": " << setiosflags(ios::left) << setw(5) << p->elem.weight << endl;
        p = p->next;
    }
    cout<<"-----------------------------------"<<endl;
    return OK;
}