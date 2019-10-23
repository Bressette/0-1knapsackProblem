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

int *sortIndex(int *sortedIndices, int size, int *costWeightRatio, int *sortedRatio)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(sortedRatio[i] == costWeightRatio[j])
            {
                sortedIndices[i] = j;
                break;
            }
        }
    }

    return sortedIndices;
}

void knapsackSolve(int *cost, int *weight, int numItems, int maxWeight)
{
    float *costWeightRatio = malloc(sizeof(float) * numItems);
    int *solutionIndex = malloc(sizeof(int) * numItems);
    int currentWeight = 0;
    int currentItem = 0;
    int numSolutionItems = 0;

    for(int i = 0; i < numItems; i++)
    {
        costWeightRatio[i] = (float)(cost[i])/(float)(weight[i]);
    }

    float *sortedRatio = malloc(sizeof(float) * numItems);
    int *sortedWeight = malloc(sizeof(int) * numItems);


    for(int i = 0; i < numItems; i++)
    {
        sortedRatio[i] = costWeightRatio[i];
    }

    int *sortedIndex = malloc(sizeof(int) * numItems);

    mergeSort(sortedRatio, 0, numItems-1);

    sortedIndex = sortIndex(sortedIndex, numItems, costWeightRatio, sortedRatio);


    while(currentWeight < maxWeight && currentItem < numItems)
    {
        if((currentWeight + weight[sortedIndex[currentItem]]) <= maxWeight)
        {
            currentWeight += weight[sortedIndex[currentItem]];
            solutionIndex[numSolutionItems++] = sortedIndex[currentItem++];
        }
        else
            currentItem++;
    }


    printf("The indices of the items that should be selected are: ");
    printIntArray(solutionIndex, numSolutionItems);

    int profit = 0;
    for(int i = 0; i < numSolutionItems; i++)
    {
        profit += cost[solutionIndex[i]];
    }

    printf("The total profit is: $%d\n", profit);



}



int main()
{
    srand(time(0));
    int numItems = 10;
    int *cost, *weight, *solutionIndices;
    cost = malloc(sizeof(int) * numItems);
    weight = malloc(sizeof(int) * numItems);
    solutionIndices = malloc(sizeof(int) * numItems);

    generateItems(cost, weight, numItems);
    printf("The price of each item is: \n");
    printIntArray(cost, numItems);
    printf("The weight of each item is: \n");
    printIntArray(weight, numItems);


    knapsackSolve(cost, weight, numItems, 30);

    return 0;
}
