#include <stdio.h>
int main()
{
	unsigned int n;	
	int x, count=1;
	scanf ("%d", &n);
	for (int i=0;i<n;i++){
		scanf("%d",&x);
		count*=x;
	}
	printf ("%d", count);
	return 0;
}
