#include <stdio.h>
#include <stdlib.h>

void swap(int * a, int * b){

	int  temp;
	temp = *a;
	*a = *b;
	*b = temp;

}

void selection(int num, int  Arr[]){

	int ind1;
	ind1 =0;


	for (int i = 0; i < num; ++i)
	{
		ind1 = i;
		for (int j = i; j < num; ++j)
		{
				if(Arr[j]<Arr[ind1]){
				ind1 = j;
			}
			/* code */
		}
			swap(&Arr[ind1],&Arr[i]);
		
		/* code */
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

	selection(num, Arr);

	for (int i = 0; i < num; ++i)
	{
		printf("%d ",Arr[i]);
		/* code */
	}

	return 0;
}