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

printArray(int *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
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

    return 0;
}
