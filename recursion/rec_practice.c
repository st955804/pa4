#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int power(int base, int exponent){
    if (exponent == 0){
        return 1;
    }
    return base * power(base, exponent - 1);

}

int crazySum(int n){
if (n == 1){
    return 1;
}
return power(n, n) + crazySum(n-1);
}


void rec2(int x){
    if (x == 0){
        return;
    }
    rec2(x-1);
    printf("%d ", x); 
}


int question3(int a, int b ){
    if (a == 0){
        return b;

    }
    if (b == 0){
        return a;
    }
    return question3(10 * a + b % 10, b/10);
}

int main(void){

    printf("%d \n", question3(10, 101));

    // printf("%d\n", crazySum(3));
    // printf("%d\n ", crazySum(4));




    // rec2(5);
    // printf("\n");
    return 0;
}