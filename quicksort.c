#include <stdio.h>
#include <stdlib.h>

int partition (int* array, int start, int end){
       int marker = start;
       for ( int i = start; i <= end; i++ ) 
       {
           if ( array[i] <= array[end] ) 
           {
               int temp = array[marker]; // swap
               array[marker] = array[i];
               array[i] = temp;
               marker += 1;
           }
       }
       return marker - 1;
   }
  
void quicksort (int array, int start, int end){
   if ( start >= end )
       return;
   int pivot = partition (array, start, end);
   quicksort (array, start, pivot-1);
   quicksort (array, pivot+1, end);
}

int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
        scanf("%d",arr+i);
    quicksort(arr,0,n-1);
    for(int i=0;i<n-1;i++)
        printf("%d ",arr[i]);
    printf("%d\n", arr[n-1]);
    return 0;
}
