void insertionSort(int arr[], int n){
    for (int i = 1; i < n; i++){
        int hand = arr[i];
        //compare i book with all previous books 
        int j;
        for ( j = i - 1; j >= 0; j--){
            if(arr[j] > hand ){
                arr[j+1] = arr[j];
            }
            else {
                break;
            }
        }
    // this works because we go into loop at j = 0
    // so arr[0] = hand for 3,4,5,2 example 
    arr[j+1] = hand;
        
    }
}