/* C program for  implementation Binomial heaps*/
//Name :- Amarnath
//Date modified :-  20/11/16
//https://stackoverflow.com/questions/1595333/algorithm-for-merging-two-max-heaps/1595703#1595703 (Arrays H1&H2 based on this)
//  Created  on 14/11/16.
//  Copyright © 2016 . All rights reserved.
//
// Maximum rank taken is 10
/*
Maintaining the heap in H1
the newly inserted element is stored as new Heap in H2
H3 is used to union the tow heaps H1,H2 and X1,X2 denote the number of trees in the heap H1 and H2 respectively

In deletion the child of the deleted node will be stored in H2 and that particular tree is deleted in the H1 and then H3 is called

In union the Heaps H1 and H2 are unioned by storing them in H3 

In H3 the heaps are stored in increasing order of the order of the trees

then we merge each of the adjacent trees 

Ex 
Order are 1,1,1,1,1,2,2,3,3,3,4,5

-> [1,1],1,1,1,2,2,3,3,3,4,5     {1,1} are merged and the first value is noted as null and the other one is replaced with a merged tree of order 2
-> N,[2,1],1,1,2,2,3,3,3,4,5    here the order of ith value is less than the order of i+1 th value so swapping the values and decrease the i by 2 as the ith element may have the same order as i+2th
-> N,1,[2,1],1,2,2,3,3,3,4,5    here again the order of ith value is less than the order of i+1 th value so swapping the values and decrease the i by 2 as the ith element may have the same order as i+2th
-> N,[1,1],2,1,1,2,2,3,3,3,4,5  now combine these and move to next

so on do till we reach the null the union is implemented in the following way

In merge the tree with higher values goes as a child to the tree with greater order increasing the order of the lesser value tree 

*/
#include <stdio.h>
#include <stdlib.h>

// Struct declaration
struct list_el
{
    
    int key,degree;
    struct list_el * parent;
    struct list_el * child;
    struct list_el * right;
}item_default={0,0,NULL,NULL,NULL}; //Default values

typedef struct list_el item;

//first 10 for roots and second 10 for  deleted_roots_children/insert
item * H1[10]={NULL},* H2[10]={NULL},*H3[20]={NULL};//H1 is the head of the Binomial heap
//for Array H1&H2
int x1=0,x2=0;//x1 is the no of heaps trees in the heap
//To clear the any left values to NULL
void clean2()
{
    for(int i=0;i<10;i++)
    {
        H2[i]=NULL;
    }
    x2=0;
    return;
}
void clean1()
{
    for(int i=0;i<10;i++)
    {
        H1[i]=NULL;
    }
    x1=0;
    return;
}
void clean3()
{
    for(int i=0;i<20;i++)
    {
        H3[i]=NULL;
    }
    return;
}


//To merge two binary trees of same order
item * union_trees(item*p1,item*p2)
{
    item * s;
    //for zero order tree
    if(p1->degree==0)
    {
        
        if(p1->key<p2->key)
        {
            // Assigning small as a parent to bigger one
            p2->parent=p1;
            p1->child=p2;//combining the bigger one and smaller one
            p1->degree++;//the degree of smaller one increases
            p2->child=p2->right=p1->right=p1->parent=NULL; // As its a 0 degree tree both rights are null
            s=p1;//returning the combined final tree
        }
        else if(p2->key<=p1->key)
        {
            // lly to the upper one but to the different tree
            p1->parent=p2;
            p2->child=p1;
            p2->degree++;
            p1->child=p1->right=p2->right=p2->parent=NULL;
            s=p2;
        }
    }
    else
    {
        
        if(p1->key<p2->key)
        {
            //Moving a bigger value tree to children of smaller value tree
            p2->parent=p1;
            p2->right=p1->child;//the child of smaller one will now be the right to bigger value one
            p1->child=p2;
            p1->parent=p1->right=NULL;
            p1->degree++;
            s=p1;
        }
        else if(p2->key<=p1->key)
        {
            
            p1->parent=p2;
            p1->right=p2->child;
            p2->child=p1;
            p2->parent=p2->right=NULL;
            p2->degree++;
            s=p2;
            
        }
        
    }
    return s;
}

// Two merge two heaps(H1,H2 globally defined)
void union_heaps()
{
    item *pass1,*pass2,*get,*temp;
    int i,j,k;
    pass1=H1[0];
    pass2=H2[0];
    //loading the values to the array H3 where we merge the trees of the two heaps in the increasing order
    for(i=0,j=0;i<10;i++)
    {
        // copying the values of H1  to H3 
        if(pass1!=NULL && pass1->degree==i)
        {
            H3[j]=pass1;
            pass1=pass1->right;
            j++;
        }
        // copying the values of H2  to H3 
        if(pass2!=NULL && pass2->degree==i)
        {
            H3[j]=pass2;
            pass2=pass2->right;
            j++;
        }
    }
    
    k=j;
    // cleaning the Heap 1 and inserting the new heap that is created after union in H3
    clean1();

// starting the merge of two trees and goes as explained in line 14
    for(i=0;i<k-1;i++)
    {
        // if the order of ith is greater than i+1 th then swap it and decrease i by 2
        if(H3[i]!=NULL && H3[i]->degree>H3[i+1]->degree)
        {
            // swapping the trees
            temp=H3[i+1];
            H3[i+1]=H3[i];
            H3[i]=temp;
            // decreasing the i by 2 
            i=i-2;
        }
        // If the two trees have same degree combine them
        else if(H3[i]!=NULL && H3[i]->degree==H3[i+1]->degree)
        {
            // merging the two trees
            pass1=H3[i];
            pass2=H3[i+1];
            get=union_trees(pass1,pass2);//calling the union funtion
            H3[i]=NULL;
            H3[i+1]=get;//storing the resultant tree in the array
        }
        
    }

    //assigning the resultant heap to Head and connecting their right parts
    for(i=0,j=0;i<k;i++)
    {
        // assigning the new Heap to H1 after union
        if(H3[i]!=NULL)
        {
            H1[j]=H3[i];
            j++;
        }
    }
    
    x1=j;
    //connecting all tress to the right that is theri siblings
    for (i=0; i<x1-1; i++) {
        H1[i]->right=H1[i+1];
    }
    H1[i]->right=NULL;
    //arasing the stored array in H2,H3
    clean2();
    clean3();
    
}


// inserts a new value in the heap

void insert(int value)
{
    //memory allocation
    item *new_ele = (item *) malloc(sizeof(item));
    // values that need to be intialised(default)
    new_ele->key=value;
    new_ele->degree=0;
    new_ele->right=NULL;
    // arrasing the H2 and store the new tree of order 0 the entered element
    clean2();
    // storing in new element head
    H2[0]=new_ele;
    // the number of trees in H2 is noted in X2
    x2=1;
    // combining the heaps if the heap H1 is empty simply copy the new element in it as head
    if((x2==1 && x1==0))
    {
        H1[0]=H2[0];
        x1++;
        clean2();
        
    }
    else
    {
        //calling union heaps with combines two heaps
        union_heaps();
    }
    clean2();
    return;
}


// return minimum value in the heap
item *minimum()
{
    item*temp=H1[0];
    //go through the tree heads and note the smallest of them
    for (int i=1; i<x1; i++) {
        if(temp->key>H1[i]->key)
        {
            temp=H1[i];
        }
    }
    return temp;
}

// deleting the minimum value
void delete_minimum()
{
    // if teh heap is empty then return saying that no heap exist
    if(x1==0)
    {
        printf("\nBinomial Heap is empty\n");
        clean1();
        return;
    }
    int j=0,k;
    item*temp=H1[0];
    //if the heap contains only one element then heap will be emptied after deleting
    if(x1==1 && H1[0]->degree==0)
    {
        printf("\nElement deleted!!\nHeap is empty\n ");
        H1[0]=NULL;
        clean1();
        //deallocating the memory
        free(temp);
        //as heap is now empty making the number of trees in heap as o
        x1=0;
        return;
    }
    // else find the least value in the heap by traversing through tree heads
    for (int i=1; i<x1; i++) {
        if(temp->key>H1[i]->key)
        {
            temp=H1[i];
            // note the index where the least element exists
            j=i;
        }
    }
    // clear the least value tree in the heap by storing it in temp
    H1[j]=NULL;
    // connected the left and right trees of the deleted tree in the heap
    if(j>0)
    {
        H1[j-1]->right=H1[j+1];
    }
    // moving all the trees after the deleted tree one step front as all trees are stored in array
    for (k=j; k<x1-1; k++) {
        H1[k]=H1[k+1];
    }
    // assign last value as null
    H1[x1-1]=NULL;
    // decrease x1 by one that is number of trees by one
    x1--;
    
    item * t1;
    // note the children of the tree and store them in Heap H2
    t1=temp->child;
    // note the number of children it has
    x2=temp->degree;
    
    int i=temp->degree-1;
    H2[i]=t1;
    // connect all the child trees of the deleted one in increasing value of their order
    for (i--; i>=0;i--) {
        H2[i]=t1->right;
        t1=t1->right;
        
    }
    // assign null to the last tree in the heap so as it doesn't have any siblings 
    if(x2>0)
    {
        H2[x2-1]->right=NULL;
    }
    // connect all the trees in the heap 2 that is the heap that has the children of teh deleted node
    for(i=0;i<x2;i++)
    {
        if(H2[i]!=NULL)
        {
            H2[i]->right=H2[i+1];
        }
    }
    // call the union to combine the two heaps
    union_heaps();
    // arase the heap 3 and h2
    clean3();
    clean2();
    // free the temp variable
    free(temp);
    printf("\nElement deleted!!\n");
    return;
    
}

int main()
{
    item * s;
    // H1[0] is the head of the binomial heap 
    clean1();
    int value,choice;
    // Prompt for choices available
    printf("Enter your choice based on these :\n1:insert\n2:Minimum\n3:Delete_Minimum\n4:quit\n");
    while(1)
    {
        printf("\nThe number of binomial trees %d\n",x1);
        for(int i=0;i<x1;i++)
        {
            printf("\t%d----%d\t",H1[i]->key,H1[i]->degree);
        }
        printf("\n");
        // Prompt user to choose for every loop
        printf("Enter your choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            // ask for the number to be inputted
                printf("Enter the Value:");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
            // call minimum for getting the minimum value
                s=minimum();
                if(s!=NULL)
                {
                    printf("\nThe minimum key is %d has a degree %d \n",s->key,s->degree);
                }
                else
                    printf("\nHeap is empty\n");
                break;
            case 3:
            // delete the minimum value
                delete_minimum();
                break;
            case 4:
            // abort the program
                abort();
                break;
            default:
                printf("U have entered wrong option!!\n");
                break;
        }
    }
    return 0;
}
