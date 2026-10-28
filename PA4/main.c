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
    // if m1's score at key is less
    if(m1->scores[key] < m2->scores[key]){
        return -1;
    }
    if(m1->scores[key] > m2->scores[key]){
        return 1;
    }
    else if(m1->scores[key] == m2->scores[key]){
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
// start at index 1, compare previous
// take it in hand, compare key with previous until it is greater than the previous one OR it's the last element 
// slide the previous ones forward
void insertionSort(Monster **list, int low, int high, int key){

}

// Performs Merge Sort on list[low..high] according to key.
// merge function from class
void mergeSortRec(Monster **list, int low, int high, int key){
    if (high - low + 1 <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }
}

// Merge Sorts the array list of size n according to key.
void mergeSort(Monster **list, int n, int key){

}

// Quick Sorts the array list of size n according to key
void quickSort(Monster **list, int n, int key){

}

// Performs Quick Sort on list[low..high] according to key.
void quickSortRec(Monster **list, int low, int high, int key){
    if (high - low + 1 <= BASECASESIZE) {
        insertionSort(list, low, high, key);
        return;
    }
}

int main (void){

    int count;
    scanf("%d", &count);
    for(int i = 0; i < &count; i++){
        Monster * monsterList = malloc(sizeof(Monster));
        scanf("%s %s %d %d %d", monsterList->name, monsterList->element, monsterList->scores[0], monsterList->scores[1], monsterList->scores[2]);
    }
    Monster ** overallList = malloc(sizeof(Monster *));
    Monster ** speedList = malloc(sizeof(Monster * ));
    return 0;
}