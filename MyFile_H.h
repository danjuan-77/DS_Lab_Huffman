#ifndef MYFILE_H
#define MYFILE_H

#include <cmath>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include "MyLinkList_H.h"

/*读取源文件信息，统计字符出现频率*/
Status LoadSourseText();

/*读取CodeFrequency.txt中的信息*/
Status LoadChar(LinkList &L, int &textLength, int &charNumber);

/*计算正确率*/
Status CalculateAccuracy(int n);

/*计算压缩率*/
Status CalculateCompressionRate();
#endif