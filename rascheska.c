#include <stdio.h>
#include <stdlib.h>

int rascheska(int* arr,size_t arr_len) 
{	
	int tmp,k,step=arr_len,swaps=0;
	while(arr_len>1) {
		step/=1.2473309;
		if (step<1)
			step=1;
		k=0;
		for (int i=0; i+step<arr_len;i++) {
			if(arr[i]>arr[i+step]) {
				int t=arr[i];
				arr[i]=arr[i+step];
				arr[i+step]=t;
				swaps++;
				k=i;
			}
		}
		if (step==1)
			arr_len=k+1;
	}
	return swaps;
}

int main(){
	int n;
	scanf("%d",&n);
	int arr[n];
	for(int i=0;i<n;i++)
		scanf("%d",arr+i);
	rascheska(arr,n);
	for(int i=0;i<n-1;i++)
		printf("%d ",arr[i]);
	printf("%d\n", arr[n-1]);
	return 0;
}
