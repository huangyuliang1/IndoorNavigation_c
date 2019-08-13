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
			i = strlen(strLine) / 2 - 21;   //��Ϊcsv�ļ��Զ���','��Ϊ�ָ��������Դ˴�����2
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
    // ���ļ�
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
                ptr = strtok(strLine,",");//�����ַ��������ַ���,��֮ǰ���ַ���ʣ�µı�������̬�����У��˷���vs��Ϊ����ȫ��
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
                    ptr = strtok(NULL,","); //�����ļ��ж�ȡ�ĵ�ǰ��ʣ���ַ����飬��ȡ�ַ���,��ǰ����ֽ�
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
// �ͷŶ�̬�����ڴ�
void FreeCsvData(TD *giCsvData){
	printf("2");
    free(giCsvData);
    giCsvData = NULL;

}
// ͨ��ָ��*giCsvData�����ݶ�̬�����ڴ�ռ�
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




