/* C program for  heapsort */
//Name :- Amarnath
//Date modified :-  20/11/16
//
//  Created  on 12/11/16.
//  Copyright © 2016 . All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>

// calles it's self untill the heap satisfies it's condition
void heapify(int H[],int n,int r)
{
    int root = r;
    int left=2*root+1;
    int right=2*root+2;
    
    // finding the smallest ones in the right and left and root
    if(left<n && H[left]>H[root])
    {
        root = left;
    }
    if(right<n && H[right]>H[root])
    {
        root = right;
    }
    // replace the smallest one in the root if root isn;t the smallest one
    if(root != r)
    {
        int temp = H[root];
        H[root]=H[r];
        H[r]=temp;
        heapify(H,n,root);
    }
	
    
}

// constructing the heap for satisfying the heap property
void constheap(int H[],int size)
{
    // starting it from the half of the array as other half are the leafs and doesn't have the children
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(H, size, i);
}

// for sorting the array
void heap_sort(int H[],int size)
{
    constheap(H, size);
    int temp;
	// for getting the highest value and replace it with the last
    for(int i=size-1; i>=0; i--)
    {
        temp = H[0];
        H[0]=H[i];
        H[i]=temp;
        heapify(H,i,0);
    }
}

// printing the heap
void printheap(int H[], int size)
{
    printf("\n{ ");
    for(int i=0;i<size;i++)
    {
        printf(" %d ,",H[i]);
    }
    printf("\b }\n\n");
}

// main the start of the function
int main()
{
	// the size of the array
    int size;
    printf("Enter the size of the list: ");
    scanf("%d",&size);
    int H[size];
    printf("Enter the %d elements : \n",size );
	// prompt the user for the input of the numbers in the heap to be sorted
    for(int i=0;i<size;i++){
        scanf("%d",&H[i]);
    }
	// calling the heap to sort the array
    heap_sort(H,size);
	// printing the heap the sorted aray
    printheap(H,size);
    return 0;
}