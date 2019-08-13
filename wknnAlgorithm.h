#pragma once
#define swaper(a,b) ((a)=(a)+(b),(b)=(a)-(b),(a)=(a)-(b))
//#define MALLOC(number,type) ((type *)malloc((number) * sizeof(type)))

double europeanDistance(double *trainData, double *testData);
Point *wknnAlgorithm(TD *trainData, double *testData, int k);
int *getSortedDistanceIndex(double *arrayer);
int *assignSpaceForData(int num);
void showPoint(Point *pt);
