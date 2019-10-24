#include "stdlib.h"
#include "stdio.h"
#include "time.h"

//Function that generates random prices and weights for items using rand()
int generateItems(int *cost, int *weight, int numItems)
{
    for(int i = 0; i < numItems; i++)
    {
        cost[i] = rand() % 100 + 1;
        weight[i] = rand() % 20 + 1;
    }
}

//function that prints an int array
void printIntArray(int *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//function that prints a float array
void printFloatArray(float *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%f ", array[i]);
    }
    printf("\n");
}

//Function that merges subarrays from merge sort
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


/*function that implements mergeSort to sort a float array by splitting
 *an array into subarrays using recursion and merging the subarrays
 *into a sorted array
 */
void mergeSort(float *array, int start, int end)
{
    if(start == end)
        return;

    int mid = (start+end)/2;

    mergeSort(array, start, mid);
    mergeSort(array, mid+1, end);

    merge(array, start, end);
}

//function that sorts the index for the new sorted ratio
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

/*Function that solves the 0-1 knapsack problem by creating a cost-to-weight
 *ratio that is then sorted to give the best items to add to the knapsack.
 *The ratio is sorted and the indices are updated for the sorted ratio and
 *held in an array that is used for accessing the elements that relate to
 *the sorted ratios. Then the elements are added to the knapsack until the
 *knapsack is filled or there are no more items that can be added
 *and the solution is printed to the console
 */
void knapsackSolve(int *cost, int *weight, int numItems, int maxWeight)
{
    float *costWeightRatio = malloc(sizeof(float) * numItems);
    int *solutionIndex = malloc(sizeof(int) * numItems);
    int currentWeight = 0;
    int currentItem = 0;
    int numSolutionItems = 0;
    int profit = 0;

    //creates cost to weight ratio and stores it in costWeightRatio[]
    for(int i = 0; i < numItems; i++)
    {
        costWeightRatio[i] = (float)(cost[i])/(float)(weight[i]);
    }

    float *sortedRatio = malloc(sizeof(float) * numItems);
    int *sortedWeight = malloc(sizeof(int) * numItems);

    //copies the ratio into sortedRatio
    for(int i = 0; i < numItems; i++)
    {
        sortedRatio[i] = costWeightRatio[i];
    }

    int *sortedIndex = malloc(sizeof(int) * numItems);
    //sorts the cost to weight ratio
    mergeSort(sortedRatio, 0, numItems-1);

    //maps the old indices to the order of the elements in the sorted ratio
    sortedIndex = sortIndex(sortedIndex, numItems, costWeightRatio, sortedRatio);

    /*selects the items by adding the elements from the sorted ratio if they can be added
     *without exceeding the total weight and continues until all items have been checked or
     *the max weight is reached
     */
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


    //prints the elements that should be added to the knapsack
    printf("The indices of the items that should be selected are: ");
    printIntArray(solutionIndex, numSolutionItems);
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

    //initialize cost, weight arrays and print their contents
    generateItems(cost, weight, numItems);
    printf("The price of each item is: \n");
    printIntArray(cost, numItems);
    printf("The weight of each item is: \n");
    printIntArray(weight, numItems);

    //solves the problem and prints the solution in the function
    knapsackSolve(cost, weight, numItems, 30);

    return 0;
}
