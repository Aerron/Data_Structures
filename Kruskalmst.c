/* C program for  implementation krushkal algorithm*/
//Name :- Amarnath
//Date modified :-  20/11/16
//
//  Created  on 13/11/16.
//  Copyright © 2016 . All rights reserved.
//

/*
ms[] array this is to store the vertices that are present in mst to check the cyclic condition 
vertices , edges are globally defined for no of verices and edges respectively
*/

#include <stdio.h>
#include <stdlib.h>

long int vertices,edges;



// To store the source , destination and weight of an edge
typedef struct{
    long int s,d,w;
}edge;


// It takes the input from the user about the information of all the edges of the graph
// asking user for the input
void create_graph(edge graph[])
{
    printf("\nEnter the source,destination,weight of each edge!\n");
    // Loop for taking the input from the user the number of edges is EDGES defined as global variable
    for (long int i=0;i<edges;i++)
    {
        // for non positive input from the user
		reenter:
        // source input of an edge
        printf("Enter the source of edge %ld : ",i);
        scanf("%ld",&graph[i].s);
        // destination input of an edge
        printf("Enter the destination of edge %ld : ",i);
        scanf("%ld",&graph[i].d);
        // weight input of the edge
        printf("Enter the weight of edge %ld : ",i);
        scanf("%ld",&graph[i].w);
		// if user gives a weight less than zero
		if(graph[i].w<=0)
		{
			printf("\nPlease enter a positive weight!\n");
			goto reenter;
		}
    }
    // printing after taking values of all the edges
    printf("\nSuccesfly completed building an adjacencylist\n");
    return;
}

// for printing the graph  mst[] array contains all the edges of the minimum spanning tree
void print(edge mst[],long int j)
{
    // for printing the graph of completed mst which have j edges
    printf("\nSource ---- Destination ------ weight\n");
    for(long int i=0;i<j;i++)
    {
        // printing the values of the source destination and weight of the edge
        printf("\n %ld     ---- %ld     ----- %ld \n",mst[i].s,mst[i].d,mst[i].w);
        
    }
    return;
}



// for the entrance of the values in the array to check mst graph cycle
// making all the vetices values in ms array will be stored as the smallest value among them so that to know if every one of them are connected 
// making the values of all the vertices to one of the vertex value among them i.e making all those vertex to be one for checking the cyclic condition
void sel(long int ms[],long int a,long int b)
{
	// if both the vertices aren't taken then the edge values in ms array would be 0 which need to be changes as they are entered into the mst
    if(ms[a+1]==0 && ms[b+1]==0)
    {
		// entering the values in the array ti.e the least of the both vertex 
        // if 3,4 are connected and their values are 0 in ms array the their both values will become 3 in the ms arry i.e ms[3]=ms[4]=3
        // assinging the least of those values in the array just for convenction either big one too can be used as the convenction that they both are connected
        if(a<b)
        {
        ms[b+1]=a+1;
        ms[a+1]=a+1;
        }
        else
        {
        ms[b+1]=b+1;
        ms[a+1]=b+1;
        }
    }
	
	// if both the vertex have diffecrent values that means the edge connected them isn't included in the mst but the vertices are included in the mst 
    // taking this edge into mst would not violate the cyclic condition as the they aren't forming a cyclic graph even though they are in mst they both are not connected
    else if(ms[a+1]!=0 && ms[b+1]!=0)
    {
		// entering the least value among them in the into all the vertices the other one is connected to
        /*
        if 3,4,5,6,1,9,2 are in mst ut 3,4,5,6 are connected and 1,9,2 are connected seperately 3,4,5,6 are  connected ms[3],ms[4],ms[5],ms[6] would have 3  and 1,9,2 are connected seperately then ms[1]=ms[9]=ms[2] will have 1 
        so connected 3 and 1 isn't a problem as they don't form a cycle and should make all the vales of ms array of 3,4,5,6,1,9,2 as 1 as these all are connected now i.e replacing the values with the least value of the vertex in the connected vertices
        */

        // if a>b then a's ms value would be assigned to all the vertices connected to b
        if (a<b)
        { long int k=ms[b+1];
            // traversing through all the ms array to find which are connected to b and making them to a's value in the ms array
            for (long int i = 1; i <= vertices; ++i)
            {
                // if it's a connected vertex to b then it's value will be k that is ms[b+1] so changing to a's value in the ms array
                if(ms[i]==k)
                {
                    // changing all the connected vertex values to a particular value 
                    ms[i]=ms[a+1];
                }
                
            }

        }

        // if a>b then b's ms value would be assigned to all the vertices connected to a
        else{
            long int k=ms[a+1];
            // going through all the vertices and changing the values of the vertices connected to a
                for (long int i = 1; i <= vertices; ++i)
                {
                    if(ms[i]==k)
                    {
                        ms[i]=ms[b+1];
                    }
                   
                }
        }
    }
	// if only one of them is present in the mst then assign the ms of the present one to ms of the other so that it is connected to vertices connected to the vertex of other one in mst
    else
    {
        // finding which one isn't in the mst and just included that value will be changed
        if(ms[a+1]!=0)
        {
            ms[b+1]=ms[a+1];
        }
        else
        {
            ms[a+1]=ms[b+1];
        }
    }
	
    
    return;
}


// to check if the edge can be inseted into mst i.e thhe edge that doesn't form a cyclic graph
long int check(long int ms[],long int a,long int b)
{
	// if both are not entered then ms value of the vertex will be 0 
    if (ms[a+1]==0 && ms[b+1]==0)
    {
        return 1;
    }
	// if the valuess are included in the mst then the values of those both would be same(other than 0 as 0 is checked which means they are not in the mst) if the edge connecting them is forming a cycle so returning 0
    else if(ms[a+1]==ms[b+1])
    {
        return 0;
    }
	// in other case it can be used as the edges have different values 
    // i.e combining all the edges that are connected 
    // 3,4,5,6 are connected nad they are in mst then the value of them in the ms array  would be 3 at the same time 1,7,9,11 are connected then the values of them would be 1 so connecting edge 1 and 3 would not be a problem
    // so if those values in ms aren't same they can be used
    else 
    {
        return 1;
    }
}



void Kruskalmst(edge graph[],long int ver,edge mst[])
{
    long int V=ver;
    // temporary struct for storing and swapping the structs of edges
    edge temp;
    // storing the value of ms[i]=edge number to check the cyclic graph
    long int ms[V+1];// to check the cyclic
    long int i,j,k=0;
    // first assigning all the values in the array to be 0 
    for(i=0;i<vertices;i++)
    {
        ms[i]=0;
    }
    
    //Selection sort of all the edges as a part of the algorithm
    for(i=0;i<edges-1;i++){
        for(j=i+1;j<edges;j++){
            if(graph[i].w>graph[j].w)
           	{
                // swapping the variables
                temp=graph[i];
                graph[i]=graph[j];
                graph[j]=temp;
          		}
        }
    }
    // printing the graph after the sorting of all edges
    print(graph,edges);
    long int x;
    // the loop to select the edges for mst
    for(i=0;i<ver-1;i++)// stop if vetices-1 edges includs in an mst
    {
        j=0;
        // looping till we get an edge that isn't forming a cyclic graph and then stopping the loop by changing the value of j to 1
        while(j==0)
        {
			//Check functin checks if the edge can be inserted in the mst which doesn't form a cycle
			 x=check(ms,graph[k].s,graph[k].d);
            // if x=1 enter it in the mst
            if(x==1)
            {
                // increasing the j to 1 to terminate the loop as x is 1 which means the edge is taken into the graph
                j++;	
                // entering it into the ith edge in the mst 
                mst[i]=graph[k];
                // change th value in array ms for note  the edges that are inserted in the mst
                // the vertices of the edge are now present in the mst must be changed in ms array for future reference to check if it's forming a cyclic graph
				sel(ms,graph[k].s,graph[k].d);
        
            }
            // increasing the k that is the Kth edge in the edges database
            k++;
        }
    }
    
    return;
}

// start of the function
int main()
{
    // v as the temporary variable
    long int v;
	// prompt for user input for the number of the vertices
    printf("Enter the number of vertices in the graph : ");
    scanf("%ld",&v);
    vertices =v;
    // entering the value of the vertices in the global variable VERTICES
	// prompt for the edges
    printf("Enter the number of edges : ");
    scanf("%ld",&edges);
    // finding the number of edges does a graph contain and creating a edge array of struct edge
    //creating a graph array of structs that contain all the edges
    edge g[edges];
	// calling create which asks the user for the input
    create_graph(g);
	printf("\nThe entered graph is:\n");
    // printing the inputted graph
    print(g,edges);
    // mst array maintains the mst edges that is v-1 edges
    edge mst[v-1];
	// calling the function krushkal
    Kruskalmst(g,v,mst);
    // to print the minimum spanning tree after running krushkals algorithm
	printf("\nThe minimum spanning tree is:-\n");
    print(mst,vertices-1);
    return 0;
}
