#include <stdio.h>
#include <stdlib.h>

void swap(int * a, int * b){

	int  temp;
	temp = *a;
	*a = *b;
	*b = temp;

}

void bubble(int num, int  Arr[]){

int count;
	for (int i = 0; i < num-1; ++i)
	{
		count = 0;
		for (int j = 0; j < num-i-1; ++j)
		{
				if(Arr[j]>Arr[j+1]){
				swap(&Arr[j],&Arr[j+1]);
				count = 1;
			}
		}
		if (count == 0)
		{
			break;
			/* code */
		}
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

	bubble(num, Arr);

	for (int i = 0; i < num; ++i)
	{
		printf("%d ",Arr[i]);
		/* code */
	}

	return 0;
}