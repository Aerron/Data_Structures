#include <stdio.h>
#include <stdlib.h>



void swap(int * a, int * b){

	int  temp;
	temp = *a;
	*a = *b;
	*b = temp;

}


int partition(int arr[], int low, int high)
{

	int pivot = arr[high];   
    int i = (low - 1);  
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);

}


void quickSort(int Arr[], int l, int r)
{
    if (l < r)
    {
        int m = partition(Arr, l, r);

        quickSort(Arr, l, m - 1);  
        quickSort(Arr, m + 1, r); 

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
		printf("%d %d \n",num, i );
		scanf("%d", &Arr[i]);
		/* code */
	}

	quickSort(Arr, 0, num-1);

	for (int i = 0; i < num; ++i)
	{
		printf("%d ",Arr[i]);
		/* code */
	}

	return 0;
}