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

void printArray(int *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int min(int *array, int size)
{
    int minimum = array[0];

    for(int i = 1; i < size; i++)
    {
        if(array[i] < minimum)
            minimum = array[i];
    }

    return minimum;
}


void merge(int *array, int start, int end)
{
    int mid = (start+end)/2;

    int i = start;
    int j = mid + 1;
    int k = start;

    int temp[100];

    while(i <= mid && j <= end)
    {
        if(array[i] < array[j])
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

void mergeSort(int *array, int start, int end)
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
    int *costWeightRatio = malloc(sizeof(int) * numItems);

    for(int i = 0; i < numItems; i++)
    {
        costWeightRatio[i] = cost[i]/weight[i];
    }

    int *sortedRatio = malloc(sizeof(int) * numItems);

    for(int i = 0; i < numItems; i++)
    {
        sortedRatio[i] = costWeightRatio[i];
    }





}



int main()
{
    srand(time(0));
    int numItems = 10;
    int *cost, *weight;
    cost = malloc(sizeof(int) * numItems);
    weight = malloc(sizeof(int) * numItems);

    generateItems(cost, weight, numItems);
    printArray(cost, numItems);
    printArray(weight, numItems);

    mergeSort(cost, 0, numItems-1);
    printArray(cost, numItems);

    return 0;
}
