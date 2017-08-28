#include <stdio.h>
#include <stdlib.h>

void swap(int * a, int * b){

	int  temp;
	temp = *a;
	*a = *b;
	*b = temp;

}

void insertion(int num, int  Arr[]){

	for (int i = 0; i < num-1; ++i)
	{
		
		int val = Arr[i+1];
		int j = i;
		
		while (Arr[j]>val && j>= 0)
			{
				Arr[j+1] = Arr[j];
				j--;
				/* code */
			}
			Arr[j+1]=val;

	}
}



int main(int argc, char const *argv[])
{
	int num;
	printf("Enter: ");
	scanf("%d", &num);
	int *Arr = (int * ) malloc((num)*sizeof(int));

	for (int i = 0; i < num; ++i)
	{
		scanf("%d", &Arr[i]);
		/* code */
	}

	insertion(num, Arr);

	for (int i = 0; i < num; ++i)
	{
		printf("%d ",Arr[i]);
		/* code */
	}

	return 0;
}