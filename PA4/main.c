/* COP 3502C PA4
This program is written by: Stuart Palmer */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAXSIZE 30
#define NUMSCORES 4
#define POWER 0
#define SPEED 1
#define STAMINA 2
#define TOTAL 3
#define BASECASESIZE 30

typedef struct Monster {
char *name;
char element[MAXSIZE + 1];
// the 3 scores are power, speed, stamina 
int scores[NUMSCORES];
} Monster;

// Returns a negative integer if the monster pointed to by m1
// comes before the monster pointed to by m2 when sorted by key.
// If the selected scores are equal, break the tie alphabetically
// using the monster's name.
// Returns 0 if the two monsters are identical according to the
// required comparison, and a positive integer if m2 comes before m1.

int compareTo(Monster *m1, Monster *m2, int key){
    // Larger scores come first for both rankings.
    if(m1->scores[key] < m2->scores[key]){
        return 1;
    }
    if(m1->scores[key] > m2->scores[key]){
        return -1;
    }
    else {
        if(strcmp(m1->name, m2->name) == 0 ){
            return 0;
        }
        // m1 comes first
        else if(strcmp(m1->name, m2->name) < 0 ){
            return -1;
        }
        else{
            return 1;
        }
    }
}

// Swap function for partition function
 void swap( Monster ** xp, Monster ** yp){
    Monster * temp = *xp;
    *xp = *yp;
    *yp = temp;
 }

int partition(Monster ** list, int left, int right, int key){

    int randIdx = left + rand()%(right-left + 1);
    swap(&list[left], &list[randIdx]);
    int pivotIdx = left;
    left++;
    
    while (left <= right){
        // Left gets stuck when not true    
        while(left <= right && compareTo(list[left], list[pivotIdx], key) <= 0 ){
            left++;
        }

        // Right gets stuck when not true
        while(left <= right && compareTo(list[right], list[pivotIdx], key) > 0 ){
            right--;
        }

        // Before swapping right and left
        // Checks if they should be swapped
        if (left < right){
            swap(&list[left], &list[right]);
        }
    }
    // Swaps the pivotIdx and right so pivot is at its correct spot
    swap(&list[right], &list[pivotIdx]);
    return right;

}

// Sort only list[low..high] using the class insertion sort.
void insertionSort(Monster **list, int low, int high, int key){
    int i, j;
    Monster *item;
    for (i = low + 1; i <= high; i++){
        item = list[i];
        // Move monsters that come after item one position ahead.
        for (j = i - 1; j >= low; j--){
            if(compareTo(list[j], item, key) > 0){
                list[j + 1] = list[j];
            }
            else {
                break;
            }
        }
        list[j + 1] = item;
    }
}


// Merges sorted ranges list[low..mid] and list[mid+1..high].
void merge(Monster **list, int low, int mid, int high, int key){
        int sizeLeft = mid - low + 1;
        int sizeRight = high - mid;
        // Mallocing each side's array
        Monster **L = malloc(sizeLeft * sizeof(Monster *));
        Monster **R = malloc(sizeRight * sizeof(Monster *));

        for(int i = 0; i <sizeLeft; i++){
            L[i] = list[low + i];
        }

        for (int j = 0; j < sizeRight; j++){
            // L contains mid
            R[j] = list[mid + 1 + j];
        }

        int i = 0, j = 0;
        int k = low;

        while(i < sizeLeft && j < sizeRight){
            if(compareTo(L[i], R[j], key) <= 0){
                list[k] = L[i];
                i++;
            }
            else {
                list[k] = R[j];
                j++;
            }
            k++;
        }
        while(i < sizeLeft){
            list[k] = L[i];
            i++;
            k++;
        }
        while(j < sizeRight){
            list[k] = R[j];
            j++;
            k++;
        }
        free(L);
        free(R);
}

// Performs Merge Sort on list[low..high] according to key.
void mergeSortRec(Monster **list, int low, int high, int key){
    // Call for insertion sort if <= 30
    if (high - low + 1 <= BASECASESIZE){
        insertionSort(list, low, high, key);
        return;
    }
    if (low < high){
        int mid = (low + high) / 2;
        mergeSortRec(list, low, mid, key);
        mergeSortRec(list, mid + 1, high, key);
        merge(list, low, mid, high, key);
    }
}

// Merge Sorts the array list of size n according to key.
// Wrapper that initiates call to mergeSortRec()
void mergeSort(Monster **list, int n, int key){
    mergeSortRec(list, 0, n - 1, key);
}




// Performs Quick Sort on list[low..high] according to key
void quickSortRec(Monster **list, int low, int high, int key){
    if (high - low + 1 <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }
    if (low < high){
        int split = partition(list, low, high, key);
        quickSortRec(list, low, split - 1, key);
        quickSortRec(list, split + 1, high, key);
    }
}

void quickSort(Monster **list, int n, int key){
    quickSortRec(list, 0, n - 1, key);
}

int main (void){
    int count;
    scanf("%d", &count);

    Monster **overallList = malloc(count * sizeof(Monster *));
    Monster **speedList = malloc(count * sizeof(Monster *));
    for(int i = 0; i < count; i++){
        char name[MAXSIZE + 1];
        Monster *monster = malloc(sizeof(Monster));
        scanf("%30s %30s %d %d %d", name, monster->element,
              &monster->scores[POWER], &monster->scores[SPEED],
              &monster->scores[STAMINA]);

        monster->name = malloc(strlen(name) + 1);
        strcpy(monster->name, name);
        monster->scores[TOTAL] = monster->scores[POWER] + monster->scores[SPEED] + monster->scores[STAMINA];

        // Same monsters, different lists
        overallList[i] = monster;
        speedList[i] = monster;
    }

    mergeSort(overallList, count, TOTAL);
    quickSort(speedList, count, SPEED);

    printf("Overall Expedition Ranking\n");
    for(int i = 0; i < count; i++){
        printf("%d. %-15s %d\n", i + 1, overallList[i]->name,
               overallList[i]->scores[TOTAL]);
    }

    printf("\nSpeed Challenge Ranking\n");
    for(int i = 0; i < count; i++){
        printf("%d. %-15s %d\n", i + 1, speedList[i]->name,
               speedList[i]->scores[SPEED]);
    }

    // Each monster and name is freed once through overallList.
    for(int i = 0; i < count; i++){
        free(overallList[i]->name);
        free(overallList[i]);
    }
    free(overallList);
    free(speedList);
    return 0;
}
