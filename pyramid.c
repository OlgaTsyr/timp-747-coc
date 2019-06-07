#include <stdio.h>
#include <stdlib.h>

void restore_heap(int *arr, int prev_lvl, int end){
    int maxChild,stop = 0;
    while ((prev_lvl * 2 <= end) && !stop){
        if (prev_lvl * 2 == end || arr[prev_lvl * 2] > arr[prev_lvl * 2 + 1])
            maxChild = prev_lvl * 2;
        else 
            maxChild = prev_lvl * 2 + 1;
        if (arr[prev_lvl] < arr[maxChild]){
            int t=arr[prev_lvl];
            arr[prev_lvl]=arr[maxChild];
            arr[maxChild]=t;
            prev_lvl = maxChild;
        }
        else
            stop = 1;
    }
}

int pyramid_sort(int *arr, size_t arr_len){
    int res=0;
    for (int i = (arr_len / 2) - 1; i >= 0; i--)
        restore_heap(arr, i, arr_len - 1);
    for (int i = arr_len - 1; i >= 1; i--){
        int t=arr[0];
        arr[0]=arr[i];
        arr[i]=t;
        res++;
        restore_heap(arr, 0, i - 1);
    }
    return res;
}

int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
        scanf("%d",arr+i);
    pyramid_sort(arr,n);
    for(int i=0;i<n-1;i++)
        printf("%d ",arr[i]);
    printf("%d\n", arr[n-1]);
    return 0;
}
