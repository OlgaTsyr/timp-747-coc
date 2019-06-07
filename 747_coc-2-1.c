#include <stdio.h>

int main(){
	unsigned int n;
	int x, count=0;
	scanf ("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d", &x);
		if(x<0){
			count++;
		}
	}
	printf ("%d", count);
	return 0;
}
