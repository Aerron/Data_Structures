/* C program for merge sort */
//Name :- Amarnath
//Date modified :-  28/2/16
//
//  Created by SadhuBalaAmarnath on 28/02/16.
//  Copyright © 2016 SadhuBalaAmarnath. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void merge(int msarr[], int l, int m, int r)
    {
        int i=0,j=0,k=l;
        int n1=(m-l+1),n2=(r-m);
        int temp1[n1],temp2[n2];                                       //creating temporary array for sorting

        memcpy(&temp1[0],&msarr[l],sizeof(msarr[0])*n1);                //copying the array using memcpy function included string.h
        memcpy(&temp2[0],&msarr[m+1],sizeof(msarr[0])*n2);
        
        while (j < n2 && i < n1 )                                        //finding the small value from the temp array and placing it in the real array
            {
                if (temp1[i] <= temp2[j])
                {
                    msarr[k++] = temp1[i++];                            //increasing the respective variables after assgning to original from the temp array
                }
                else
                {
                    msarr[k++] = temp2[j++];                            //increasing the respective variables after assgning to original from the temp array
                }
            }
        
        if (i < n1)                                                     //the left array is to be entered into the original array
            {
                msarr[k++] = temp1[i++];
            }
        else if (j < n2)
            {
                msarr[k++] = temp2[j++];
            }
    }

void mergeSort(int marr[], int l, int r)
    {
        if (l < r)
            {                                                               //for dividing into smaller array
                int me = (r+l)/2;
                mergeSort(marr, me+1, r);                                   //recursive function calling 
                mergeSort(marr, l, me);
                merge(marr, l, me, r);                                      //calling the sorting function
            }
    }


int main()
{
    int n,i;
    printf("Enter the number of elements in the array : ");
    scanf("%d",&n);
    int array[n];
    													                   //declaring the array of n elements
    for (i = 0; i < n; ++i)											      //asking for input
        {
            printf("Enter the array element %d : ",i+1 );
            scanf("%d",&array[i]);
        }
    
    mergeSort(array, 0, n - 1);
    
    printf("The sorted elements are : {");							       //finally printing the output
    for ( i = 0; i < n; ++i)
        {
            printf(" %d ,",array[i] );
        }
    printf("\b}\n");
    
    for (int i = 0; i < 5; ++i)  									      //for time analysis
        {
            int min,max,n;
            printf("Enter the min : ");							         //asking for min and max values to be produced by random variable
            scanf("%d",&min);
            printf("Enter the max : ");
            scanf("%d",&max);
            printf("Enter the number of elements : ");					//asking for inputs of 100,500,1000,5000 fot T analysis
            scanf("%d",&n);
            int B[n];
                for (int i = 0; i < n; ++i)
                {
                    B[i]=rand()%(max-min+1)+min;						    //generating the random variables included stdlib.h
                }
            clock_t begin,end;											//T anlysis included time.h
            begin=clock();
            mergeSort(B,0,n-1);
            end=clock();
            printf("The time taken for %d elements is : ",n);
            printf("%lf\n",(double)(end-begin)/CLOCKS_PER_SEC ); 		//Printing T analysis
            
        }

    return 0;
}