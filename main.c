#include "readCSVFile.h"
#include "wknnAlgorithm.h"

int main()
{
	char *filename1 = "D:\\Workspase\\IndoorNavigation_C\\datas\\train.csv";
	char *filename2 = "D:\\Workspase\\IndoorNavigation_C\\datas\\test.csv";

    TD trainDatas[NUM_OF_TRAIN_DATAS], *trainPot;
    trainPot = trainDatas;
    TD testDatas[MAX_NUM_DATAS], *testPot;
    testPot = testDatas;

    ifTrainData = 1;
    ReadCsvData(trainPot, filename1);
    ifTrainData = 0;
    ReadCsvData(testPot,filename2);

    int i;
    Point *preCoordinate = NULL;
    for (i = 0; i < 50; i++)
    {
        preCoordinate = wknnAlgorithm(trainPot, &((testPot + i)->signals[0]), 4);
        if (preCoordinate == NULL)
        {
            printf("Calculate preCoordinate failure!\n");
            return -1;
        }
        showPoint(preCoordinate);
    }
	//ShowCsvData(trainPot, 20);
	free(trainPot);
    free(testPot);
	return 1;
}
