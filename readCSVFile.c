#include "readCSVFile.h"

int GetTotalLineCount(FILE * fp)
{
    int i = 0;
    char strLine[MAX_LINE_SIZE];
    fseek(fp,0,SEEK_SET);
    while (fgets(strLine, MAX_LINE_SIZE, fp))
        i++;
    fseek(fp,0,SEEK_SET);
    return i;
}

int GetTotalColCount(FILE * fp)
{
    int i = 0;
    char strLine[MAX_LINE_SIZE];
    fseek(fp,0,SEEK_SET);
    if (fgets(strLine, MAX_LINE_SIZE, fp))
    {
    	printf("strlen(strLine):%s\n",strLine);
    	printf("strlen(strLine):%d\n",strlen(strLine));
    	if (ifTrainData == 1){
    		i = strlen(strLine) / 2 - 48;
		}
		else{
			i = strlen(strLine) / 2 - 21;   //因为csv文件以逗号','作为分隔符，所以此处除以2
		}
    }
    else
    {
        fseek(fp,0,SEEK_SET);
        return -1;
    }
    fseek(fp,0,SEEK_SET);
    return i;
}

void ReadCsvData(TD *csvData, char* csvFilePath)
{
    FILE* fCsv;
    char *ptr;
    char strLine[MAX_LINE_SIZE];
    int numRow;
	int numCol;
    int i;
    int j;
    // 打开文件
    fCsv = fopen(csvFilePath, "r" );
    if( fCsv == NULL )
    {
        printf("open file %s failed!\n",csvFilePath);
        return;
    }
    else
    {
        numRow = GetTotalLineCount(fCsv);
        numCol = GetTotalColCount(fCsv);

        for (i = 0; i < numRow; i++)
        {
            j=0;
            if(fgets(strLine,MAX_LINE_SIZE,fCsv))
            {
                ptr = strtok(strLine,",");//返回字符数组中字符‘,’之前的字符，剩下的保留到静态数组中（此方法vs认为不安全）
                while(ptr != NULL)
                {
                    if (j < numCol - 2)
                    {
                        (csvData+i)->signals[j] = atof(ptr);
                    }
                    else if (j < (numCol-1))
                    {
                        (csvData+i)->coordinate.x = atof(ptr);
                    }
                    else
                    {
                        (csvData+i)->coordinate.y = atof(ptr);
                    }
                    j++;
                    ptr = strtok(NULL,","); //将从文件中读取的当前行剩余字符数组，读取字符‘,’前面的字节
                }
            }
        }
    }
    fclose(fCsv);
}

void  ShowCsvData(TD *csvData,int dataNum)
{
    int i;
    int j;

    for (i = 0; i < dataNum; i++)
    {
        if (dataNum > NUM_OF_TRAIN_DATAS || dataNum > MAX_NUM_DATAS)
        {
            printf("Memory may be out of bounds!\n");
            return;
        }
        printf("Line %i :",i+1);
        for (j = 0; j < SIGNAL_NUM; j++)
        {
            printf("%.2f ",(csvData+i)->signals[j]);
        }
        printf("%.2f %.2f",(csvData+i)->coordinate.x,(csvData+i)->coordinate.y);
        printf("\n");
    }
}

/*
// 释放动态数据内存
void FreeCsvData(TD *giCsvData){
	printf("2");
    free(giCsvData);
    giCsvData = NULL;

}
// 通过指针*giCsvData给数据动态分配内存空间
TD *AssignSpaceForData(int num){
    double *p = (double*)malloc(sizeof(TD)*num);
    if (p == NULL){
        printf("Memory allocation failed!");
        return;
    }
    memset(p, 0, sizeof(TD)*num);
    return p;
}
*/




