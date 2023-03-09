#include <stdlib.h>
#include <stdio.h>

struct arrContainer_s{
    int arrlength;
    int arr[arrlength];
}; 
typedef struct arrContainer_s arrContainer;

int main(){
    arrContainer mainContainer = scanValues();
    printValues(mainContainer);

    int sum = sumValues(mainContainer);
    int min = minValue(mainContainer);
    int max = maxValue(mainContainer);

    printf("The sum: %d\n", sum);
    printf("The minimum value: %d\n", min);
    printf("The maximum value: %d\n", max);

    return 0;
}

int scanValues(){
    arrContainer x;
    int i = 0;

    printf("Enter the number of the values:");
    scanf("%d", &x.arrlength);

    printf("Enter the values!\n");

    while(i != x.arrlength-1) {
        printf("Value %d:\n", i+1);
        scanf("%d", &x.arr[i]);
    }

    return x;
}

void printValues(arrContainer x){
    int i;
    printf("The scanned values are:\n");
    for(i = 0; i < x.arrlength-2; i++) {
        printf("%d, ", x.arr[i]);
    }
    printf("%d\n", x.arr[x.arrlength-1]);
}

int sumValues(arrContainer x){
    int i, sum = 0;

    for(i = 0; i < x.arrlength-1; i++){
        sum += x.arr[i];
    }

    return sum;
}

int minValue(arrContainer x){
    int i, min=x.arr[0];

    for(i = 0; i < x.arrlength-1; i++){
        if(x.arr[i] < min) {
            min = x.arr[i];
        }
    }
    return min;
}

int maxValue(arrContainer x){
    int i, max=0;

    for(i = 0; i < x.arrlength-1; i++){
        if(x.arr[i] > max) {
            max = x.arr[i];
        }
    }
    return max;
}