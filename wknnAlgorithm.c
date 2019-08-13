#include "readCSVFile.h"
#include "wknnAlgorithm.h"
#include<math.h>
#include<assert.h>

Point *wknnAlgorithm(TD *trainData, double *testData, int k)
{
    assert(trainData != NULL);
    assert(testData != NULL);
    assert(k > 0);

    double *distances;
    int i;
    distances = (double *)malloc(sizeof(double)*NUM_OF_TRAIN_DATAS);
    if (distances == NULL)
    {
        printf("-Memory of distances allocation failure!-");
        return NULL;
    }

    for (i = 0; i < NUM_OF_TRAIN_DATAS; i++)
    {
        distances[i] = europeanDistance(&((trainData + i)->signals[0]), testData);
    }

    int *indexs = NULL;
    indexs = getSortedDistanceIndex(distances);

    double fenMu = 0.0;
    Point *preLocation;
    preLocation = (Point *)malloc(sizeof(Point));
    if (preLocation == NULL)
    {
        printf("Memory of 'preLocation' allocation failure!\n");
        return NULL;
    }
    preLocation->x = 0;
    preLocation->y = 0;

    for (i = 0; i < k; i++)
    {
        fenMu += 1.0 / distances[indexs[i]];
        preLocation->x += ((trainData+indexs[i])->coordinate.x)*(1 / distances[indexs[i]]);
        preLocation->y += ((trainData+indexs[i])->coordinate.y)*(1 / distances[indexs[i]]);
    }
    preLocation->x /= fenMu;
    preLocation->y /= fenMu;

    free(distances);
    free(indexs);

    return preLocation;
}

double europeanDistance(double *trainData, double *testData)
{
    int i;
    double distance = 0;
    for (i = 0; i < SIGNAL_NUM; i++)
    {
        distance += (trainData[i] - testData[i])*(trainData[i] - testData[i]);
    }
    return sqrt(distance);
}

int *getSortedDistanceIndex(double *arrayer)
{
	int maxpos = 0;
	int i = 0;
	int j = 0;
	int *index;

	index = assignSpaceForData(NUM_OF_TRAIN_DATAS);

    for (i = 0; i < NUM_OF_TRAIN_DATAS; i++)
    {
        index[i] = i;
    }

	for (i = 0; i < NUM_OF_TRAIN_DATAS-1; i++)
	{
		maxpos = 0;
		for (j = 1; j < NUM_OF_TRAIN_DATAS-i; j++)
		{
			if (arrayer[j] > arrayer[maxpos])
			{
				maxpos = j;
			}
		}

		if (maxpos != NUM_OF_TRAIN_DATAS - i - 1)
		{
			swaper(arrayer[maxpos], arrayer[NUM_OF_TRAIN_DATAS - i - 1]);
			swaper(index[maxpos], index[NUM_OF_TRAIN_DATAS - i - 1]);
		}
	}
	return index;
}

int *assignSpaceForData(int num)
{
    int *p = (int *)malloc(sizeof(int)*num);
    if (p == NULL)
    {
        printf("Memory allocation failure!\n");
        abort();
    }
    return p;
}

void showPoint(Point *pt)
{
    printf("x = %.2f, y = %.2f\n", pt->x, pt->y);
}


