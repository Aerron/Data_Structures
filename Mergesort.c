#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void merge(int  Arr[], int l, int m, int r){
	
	int i,j;
	i =0;
	j = 0;
	int real = l;
    int n1=(m-l+1),n2=(r-m);
    int temp1[n1],temp2[n2];                                  

    memcpy(&temp1[0],&Arr[l],sizeof(Arr[0])*n1);         
    memcpy(&temp2[0],&Arr[m+1],sizeof(Arr[0])*n2);

	while(i < n1 && j < n2 ){
		if (temp1[i]<temp2[j])
		{
			Arr[real++]= temp1[i++];
		}
		else
			Arr[real++]= temp2[j++];
	}
	while(i<n1){
		Arr[real++]= temp1[i++];
	}
	while(j<n2){
		Arr[real++]= temp2[j++];
	}

}


void merge_sort( int  Arr[], int l, int r){

	int m = (l + r )/2;
	if (l<r)
	{
		merge_sort(Arr, l, m);
		merge_sort(Arr, m+1, r);
		merge(Arr, l, m,r);
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

	merge_sort( Arr, 0, num-1);

	for (int i = 0; i < num; ++i)
	{
		printf("%d ",Arr[i]);
		/* code */
	}

	return 0;
}