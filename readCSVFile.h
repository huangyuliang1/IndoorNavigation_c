#pragma once
#include <stdio.h>
#include <memory.h> // for memset
#include <stdlib.h> // for malloc, free
#include <string.h> // for strtok

#define MAX_LINE_SIZE 256   //fgets函数读取的最大字节数
#define SIGNAL_NUM 20
#define NUM_OF_TRAIN_DATAS 158
#define MAX_NUM_DATAS 200

int ifTrainData; // 1 = train; 0 = test
typedef struct Point
{
    double x;
    double y;
}Point;

typedef struct Datas
{
    double signals[SIGNAL_NUM];
    Point coordinate;
}TD;

int GetTotalLineCount(FILE* fp);
int GetTotalColCount(FILE* fp);
void ReadCsvData(TD *csvData, char* csvFilePath);
void  ShowCsvData(TD *csvData, int dataNum);


