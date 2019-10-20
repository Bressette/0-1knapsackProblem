#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int generateItems(int *cost, int *weight, int numItems)
{
    for(int i = 0; i < numItems; i++)
    {
        cost[i] = rand() % 100 + 1;
        weight[i] = rand() % 20 + 1;
    }
}

void printIntArray(int *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printFloatArray(float *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%f ", array[i]);
    }
    printf("\n");
}


void merge(float *array, int start, int end)
{
    int mid = (start+end)/2;

    int i = start;
    int j = mid + 1;
    int k = start;

    float temp[100];

    while(i <= mid && j <= end)
    {
        if(array[i] > array[j])
        {
            temp[k++] = array[i++];
        }
        else
        {
            temp[k++] = array[j++];
        }
    }

    while(i <= mid)
    {
        temp[k++] = array[i++];
    }

    while(j <= end)
    {
        temp[k++] = array[j++];
    }

    for(int i = start; i <= end; i++)
    {
        array[i] = temp[i];
    }

}

void mergeSort(float *array, int start, int end)
{
    if(start == end)
        return;

    int mid = (start+end)/2;

    mergeSort(array, start, mid);
    mergeSort(array, mid+1, end);

    merge(array, start, end);
}

void knapsackSolve(int *cost, int *weight, int numItems, int maxWeight)
{
    float *costWeightRatio = malloc(sizeof(float) * numItems);

    for(int i = 0; i < numItems; i++)
    {
        costWeightRatio[i] = (float)(cost[i])/(float)(weight[i]);
    }

    float *sortedRatio = malloc(sizeof(float) * numItems);

    for(int i = 0; i < numItems; i++)
    {
        sortedRatio[i] = costWeightRatio[i];
    }


    printFloatArray(sortedRatio, numItems);

    mergeSort(sortedRatio, 0, numItems-1);

    printFloatArray(sortedRatio, numItems);






}



int main()
{
    srand(time(0));
    int numItems = 10;
    int *cost, *weight;
    cost = malloc(sizeof(int) * numItems);
    weight = malloc(sizeof(int) * numItems);

    generateItems(cost, weight, numItems);
    printIntArray(cost, numItems);
    printIntArray(weight, numItems);


    knapsackSolve(cost, weight, numItems, 20);

    return 0;
}
