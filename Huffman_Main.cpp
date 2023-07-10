// 主程序Main
#include <iostream>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include "MyFile_H.h"
#include "MyLinkList_H.h"
#include "MyHuffman_H.h"

using namespace std;

int main()
{
    LinkList L;
    HuffmanTree HT;
    int textLength, charNumber;
    cout << "【1】 加载文本文件，统计字符集和字符出现的次数" << endl;
    LoadSourseText(); // 加载文本文件，统计字符集和出现的次数
    Sleep(3000);

    cout << "【2】 从文件中加载字符集信息" << endl;
    LoadChar(L, textLength, charNumber); // 获取字符集和对应出现的次数，存进线性表
    Sleep(3000);
    
    cout << "【3】 构建Huffman树" << endl;
    HuffmanTreeCreate(HT, charNumber, L); // 创建Huffman树
    Sleep(3000);

    cout << "【4】 打印Huffman树" << endl;
    HuffmanTreePrint(HT, charNumber); // 打印Huffman树
    Sleep(3000);

    cout << "【5】 构建字符的Huffman编码" << endl;
    HuffmanCodeCreate(HT, charNumber, L); // 创建字符对应的Huffman码
    Sleep(3000);

    cout << "【6】 保存字符的Huffman编码" << endl;
    HuffmanCodeWrite(HT, charNumber, L); // 将字符的Huffman编码写入文件
    Sleep(3000);

    cout << "【6】 对文本文件进行Huffman编码" << endl;
    HuffmanCodeEncode(HT, L); // 对整个文本文件进行Huffman编码
    Sleep(3000);

    cout << "【7】 生成压缩文件" << endl;
    CompressionToHuf(); // 生成压缩文件
    Sleep(3000);

    cout << "【8】 计算压缩率" << endl;
    CalculateCompressionRate(); // 计算压缩率
    Sleep(3000);

    cout << "【9】 对压缩文件进行解压" << endl;
    DecompressionFromHuf(); // 对压缩文件进行解压
    Sleep(3000);

    cout << "【10】对解压得到的文件进行译码" << endl;
    HuffmanCodeDecode(HT, charNumber, textLength); // 对压缩文件进行解码
    Sleep(3000);

    cout << "【11】对译码结果计算压缩准确率" << endl;
    CalculateAccuracy(textLength); // 计算编码的准确率
    Sleep(3000);

    return 0;
}