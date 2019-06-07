#include <stdio.h>
#include <stdlib.h>

int ShellSort(int* arr,size_t arr_len)
{
	int tmp,swaps=0;
	for(int k = arr_len / 2; k > 0; k /= 2){
		for(int i = k; i < arr_len; i++)
        {
            int j;
            tmp = arr[i];
            for(j = i; j >= k; j -= k)
            {
                if(tmp < arr[j - k]){
                    arr[j] = arr[j - k];
                    swaps++;
                }
                else
                    break;
            }
            arr[j] = tmp;
        }
	}
    return swaps;
}


int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
        scanf("%d",arr+i);
    ShellSort(arr,n);
    for(int i=0;i<n-1;i++)
        printf("%d ",arr[i]);
    printf("%d\n", arr[n-1]);
    return 0;
}
