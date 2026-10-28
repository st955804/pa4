// Sorting Lab Skeleton Code


#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#define MAXARRAYS 6

#define MAXVALUE 1000000

void randArray(int arr[], int size, int maxValue);

void bubbleSort(int arr[], int n);

void insertionSort(int arr[], int n);

void selectionSort(int arr[], int n);

void merge(int arr[], int l, int m, int r);

void mergeSort(int arr[], int l, int r);

void arrayCopy(int original[], int copy[], int size);

long timediff(clock_t t1, clock_t t2);

void swap(int *xp, int *yp);

int partition(int *vals, int low, int high);

void quickSort(int *numbers, int low, int high);

void mergeInsertionSort(int arr[], int l, int r);

int main()
{
    //TODO
    int sizes[MAXARRAYS] = {10000, 20000, 30000, 40000, 50000, 60000};

    int* originalArray, *sortedArray;

    clock_t start, end;

    //difference between start and end
    long duration;

    for(int i= 0; i < MAXARRAYS; i++){

        //create the arrays and fill them with random numbers 
        originalArray = malloc(sizeof(int) *sizes[i]);
        sortedArray = malloc(sizeof(int) *sizes[i]);

        randArray(originalArray, sizes[i], MAXVALUE);
        arrayCopy(originalArray, sortedArray, sizes[i]);

        // SORTING 1: BUBBLE SORT
        start = clock();
        bubbleSort(sortedArray, sizes[i]);
        end = clock();
        duration = timediff(start, end);
        printf("\nSorting %d takes %ld milliseconds using Bubble Sort", sizes[i], duration);

         // SORTING 1: QUICK SORT
        start = clock();
        quickSort(sortedArray,0,  sizes[i] -1);
        end = clock();
        duration = timediff(start, end);
        printf("\nSorting %d takes %ld milliseconds using Quick Sort", sizes[i], duration);
        arrayCopy(originalArray, sortedArray, sizes[i]);

        // SORTING 1: INSERTION SORT
        start = clock();
        insertionSort(sortedArray, sizes[i]);
        end = clock();
        duration = timediff(start, end);
        printf("\nSorting %d takes %ld milliseconds using Insertion Sort\n", sizes[i], duration);
        arrayCopy(originalArray, sortedArray, sizes[i]);


        free(originalArray);
        free(sortedArray);

    }


    return 0;
}
//takes the 2 parameters, converts to ms
long timediff(clock_t t1, clock_t t2)
{
    //calculate the elapsed time of the passed clock_t variables using the formula below and return the value
    long elapsed = ((double) t2-t1) / CLOCKS_PER_SEC * 1000;

    return elapsed;
}

void swap(int *xp, int *yp)
{
    //swap the passed integers using pass by reference
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort(int arr[], int n)
{
    int i, j,temp;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {//then swap
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}


void insertionSort(int arr[], int n)
{
    int i, item, j;
    for (i = 1; i < n; i++)
    {
         item = arr[i];

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
          for(j=i-1; j>=0; j--)
          {
              if(arr[j]>item)
                arr[j+1] = arr[j];
              else
                break;

          }
          arr[j+1] = item;
    }
}

//this one could be used by merInsertionSort
void insertionSortModified(int arr[], int l, int r)
{
    //TODO
   
}

// check the size
// if size is now less than threshold, call insertion instead 
void mergeInsertionSort(int arr[], int l, int r)
{
    //get the size (r- l + 1) <= 25, call insertionSortModified and pass l and r
    //if you pass size, insertionSort would start from 0
    

    //else
    if (l < r)
    {
        // get the mid point
        int m = (l+r)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

       // printf("Testing l=%d r=%d m=%d\n", l, r, m);

        merge(arr, l, m, r);
    }
}

void arrayCopy(int original[], int copy[], int size)
{
    for(int i = 0; i < size; i++){
        copy[i] = original[i];
    }
}

void randArray(int arr[], int size, int maxValue)
{
    
    for(int i = 0; i < size; i++){
        arr[i] = rand()%maxValue + 1;
    }

}


void merge(int arr[], int l, int m, int r)
{
    //TODO
}

// original mergeSort


void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // get the mid point
        int m = (l+r)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

       // printf("Testing l=%d r=%d m=%d\n", l, r, m);

        merge(arr, l, m, r);
    }
}


int partition(int *vals, int low, int high)
{
  // Pick a random partition element and swap it into index low.
  int i = low + rand()%(high-low+1);
  swap(&vals[low], &vals[i]);

  int lowpos = low; //here is our pivot located.

  low++; //our starting point is after the pivot.

// Run the partition so long as the low and high counters don't cross.
  while(low<=high)
  {
    // Move the low pointer until we find a value too large for this side.
    while(low<=high && vals[low]<=vals[lowpos]) low++;

    // Move the high pointer until we find a value too small for this side.
    while(high>=low && vals[high] > vals[lowpos]) high--;

    // Now that we've identified two values on the wrong side, swap them.
    if (low<high)
     swap(&vals[low], &vals[high]);
  }

  // Swap the pivot element element into its correct location.
  swap(&vals[lowpos], &vals[high]);

  return high; //return the partition point
}

// Pre-condition: s and f are value indexes into numbers.
// Post-condition: The values in numbers will be sorted in between indexes s
//                 and f.
void quickSort(int* numbers, int low, int high) {

    // Only have to sort if we are sorting more than one number
    if (low < high) {
        int split = partition(numbers,low,high);
        quickSort(numbers,low,split-1);
        quickSort(numbers,split+1,high);
    }
}

void selectionSort(int arr[], int n)
{
    //TODO
}

