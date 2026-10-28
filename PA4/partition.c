 
 void swap(int *xp, int*yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
 }
 
 int partition(int arr[], int left, int right){

    int randIdx = left = rand()%(right - left + 1);

    swap(&arr[left], &arr[randIdx]);
    int pivotIdx = left;
    left++;

    //left gets stuck when not true 
    while(left <= right && arr[left] < arr[pivotIdx]){
     left++;
    }

    // when right gets stuck
    while(left <= right && arr[right] > arr[pivotIdx]){
    right--;
    }

    //before swapping right and left,
    // checks if they should be swapped
    if (left <= right){
        swap(&arr[left], &arr[right]);
    }

    swap(&arr[right], &arr[pivotIdx]);
    return right;
 }