
/* C program for  B trees */
//Name :- Amarnath
//Date modified :-  27/11/16
//
//  Created  on 26/11/16.
//  Copyright © 2016 . All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node_t
{
    struct node_t *ptr[6];
    int k[5];
    bool leaf;
    int count;
};

typedef struct node_t node;
node *root, *head, *head1, *temp, *par, *parent, *temp1;
int i;


void delete_leaf(node* a,int b,int c);
void delete_nonleaf(node* a,int b,int c);
void borrow_next(node* a,int b);
void borrow_prev(node* a,int b);
void merge(node* a,int b,int c);
void swap(int* a,int* b);
void Insert(int a);
void Delete(int a);
void split_child(int a,node* b,node* c);
void traverse(node* a);
void search_parent(int a,int b,node* c,int d);
void root_case(node* a);
node* find_parent(node* a,node* b);
node* succ(node* a,int b);
node* pred(node* a,int b);
node* search(node* a,int b);


void swap(int *v1, int *v2)
{
    int temp;
    temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}


void traverse(node* ele)
{
    int i;
    
    for (i = 0; i < ele->count; i++){
        if (ele->leaf == false)
            traverse(ele->ptr[i]);
        printf("%d ",ele->k[i]);
    }
    if (ele->leaf == false)
        traverse(ele->ptr[i]);
}

void sort(int s[],int n)
{
    int i,j,temp;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(s[j]>s[i])
            {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
    
}

node* create_node()
{
    node *temp = (node*)malloc(sizeof(node));
    
    temp->count = 0;
    temp->leaf = true;
    for(i=0;i<4;i++)
    {
        temp->k[i] = 0;
        temp->ptr[i]=NULL;
    }
    temp->ptr[i]=NULL;
    return temp;
}

void root_case(node *num)
{
    node* n1 = create_node();
    n1->ptr[0] = num;
    split_child(0,n1,num);
    root = n1;
}

void split_child(int x, node* n1, node* t1)
{
    n1->k[n1->count] = t1->k[2];
    (n1->count)++;
    sort(n1->k, n1->count);
    node* new = create_node();
    for(i=0;i<(t1->count-3);i++)
        new->k[i] = t1->k[i+3];
    for(i=(n1->count)-1;i>=x+1;i--)
        n1->ptr[i+1] = n1->ptr[i];
    for(i=0;i<t1->count-2;i++)
        new->ptr[i] = t1->ptr[i+3];
    new->count = t1->count-3;
    t1->count = 2;
    n1->ptr[x+1] = new;
    n1->leaf = false;
    if(t1->leaf == false)
        new->leaf = false;
}


void Insert(int data)
{
    node* j = search(root,data);
    if(j != NULL){
        printf("The element is already present in the tree\n");
        return;
    }
    temp = root;
    if(temp->leaf == false){
        search_parent(1,0,root,data);
        return;
    }
    if(temp == root && temp->count >= 4){
        temp->k[temp->count] = data;
        (temp->count)++;
        sort(temp->k, temp->count);
        root_case(temp);
        return;
    }
    temp->k[temp->count] = data;
    (temp->count)++;
    sort(temp->k, temp->count);
    
}

node* search(node* temp1, int x){
    node* j;
    while(temp1->leaf == false){
        for(i=0;i<temp1->count;i++){
            if(x == temp1->k[i])
                return temp1;
            else if(x < temp1->k[0]){
                j = search(temp1->ptr[0],x);
                return j;
            }
            else if(x > temp1->k[(temp1->count) - 1]){
                j = search(temp1->ptr[(temp1->count)],x);
                return j;
            }
            else if(x > temp1->k[i] && x < temp1->k[i+1]){
                j = search(temp1->ptr[i+1],x);
                return j;
            }
        }
    }
    for(i=0;i<temp1->count;i++){
        if(x == temp1->k[i])
            return temp1;
    }
    return NULL;
}


node* find_parent(node* par, node* j){
    if(j == root){
        parent = j;
        return j;
    }
    int i;
    for (i = 0; i <= par->count; i++){
        if (par->ptr[i]->leaf == false){
            find_parent(par->ptr[i],j);
        }
        if(par->ptr[i] == j){
            parent = par;
            return par;
        }
    }
    return NULL;
}


void search_parent(int n, int x, node* head, int data){
    int y;
    int count1 = 0;
    if(head->count >= 4){
        if(head == root){
            y = head->k[2];
            root_case(head);
            if(data > y)
                head = root->ptr[1];
            else
                head = root->ptr[0];
        }
        else{
            if(head->leaf == true){
                head->k[head->count] = data;
                (head->count)++;
                sort(head->k, head->count);
                count1 = 7;
            }
            y = head->k[2];
            split_child(x,par,head);
            if(data>y)
                head = par->ptr[x+1];
            else
                head = par->ptr[x];
        }
        
    }
    par = head;
    if(head->leaf == false){
        if(data > head->k[(head->count) - 1]){
            search_parent(n,head->count,head->ptr[head->count],data);
            return;
        }
        else if(data < head->k[0]){
            search_parent(n,0,head->ptr[0],data);
            return;
        }
        for(i=1;i<head->count;i++){
            if(data > head->k[i-1] && data < head->k[i]){
                search_parent(n,i,head->ptr[i],data);
                return;
            }
        }
    }
    else{
        temp = head;
        if(count1 == 0){
            temp->k[temp->count] = data;
            (temp->count)++;
            sort(temp->k, temp->count);
        }
        
    }
    return;
}


node* succ(node* temp1, int data){
    while(temp1->leaf == false){
        head = succ(temp1->ptr[0],data);
        return head;
    }
    return temp1;
}

node* pred(node* temp1, int data){
    while(temp1->leaf == false){
        head = succ(temp1->ptr[temp1->count],data);
        return head;
    }
    return temp1;
}


void borrow_next(node* par, int x){
    par->ptr[x]->k[par->ptr[x]->count] = par->k[x];
    par->k[x] = par->ptr[x+1]->k[0];
    for(i=0;i<(par->ptr[x+1]->count)-1;i++)
        par->ptr[x+1]->k[i] = par->ptr[x+1]->k[i+1];
    (par->ptr[x]->count)++;
    (par->ptr[x+1]->count)--;
}

void borrow_prev(node* par, int x){
    for(i=(par->ptr[x]->count);i>=1;i--)
        par->ptr[x]->k[i] = par->ptr[x]->k[i-1];
    par->ptr[x]->k[0] = par->k[x-1];
    par->k[x-1] = par->ptr[x-1]->k[(par->ptr[x-1]->count)-1];
    (par->ptr[x]->count)++;
    (par->ptr[x-1]->count)--;
}

void delete_nonleaf(node* j, int i, int data){
    head = succ(j->ptr[i+1],data);
    
    head1 = pred(j->ptr[i],data);
    if(head1->count > 2){
        swap(&head1->k[(head1->count)-1],&(j->k[i]));
        delete_leaf(head1,(head1->count)-1,j->k[i]);
    }
    else{
        swap(&head->k[0],&(j->k[i]));
        delete_leaf(head,0,j->k[i]);
    }
}

void merge(node* par, int x, int y){
    par->ptr[x]->k[par->ptr[x]->count] = par->k[x];
    (par->ptr[x]->count)++;
    for(i=0;i<par->ptr[x+1]->count;i++)
        par->ptr[x]->k[i+par->ptr[x]->count] = par->ptr[x+1]->k[i];
    par->ptr[x]->count = par->ptr[x]->count + par->ptr[x+1]->count;
    for(i=x;i<(par->count)-1;i++)
        par->k[i] = par->k[i+1];
    
    free(par->ptr[x+1]);
    if(par == root && par->count == 1){
        root = par->ptr[x];
    }
    for(i=x+1;i<par->count;i++)
        par->ptr[i] = par->ptr[i+1];
    (par->count)--;
}


void delete_leaf(node*j, int i, int data){
    int r = 0,m,z;
    find_parent(root,j);
    for(m=i;m<(j->count)-1;m++)
        j->k[m] = j->k[m+1];
    j->count = (j->count)-1;
    if(j == root)
        return;
    for(z=0;z<parent->count;z++){
        if(parent->ptr[z] == j)
            break;
        r++;
    }
    z = r;
    if(j->count < 2){
        if(z == 0 && parent->ptr[z+1]->count > 2)
            borrow_next(parent,z);
        else if(z == (parent->count) && parent->ptr[z-1]->count > 2)
            borrow_prev(parent,z);
        else if(z == 0 && parent->ptr[z+1]->count <= 2)
            merge(parent,z,z+1);
        else if(z == (parent->count) && parent->ptr[z-1]->count <= 2)
            merge(parent,z-1,z);
        else if(parent->ptr[z-1]->count > 2)
            borrow_prev(parent,z);
        else if(parent->ptr[z+1]->count > 2)
            borrow_next(parent,z);
        else if(parent->ptr[z-1]->count <= 2 && parent->ptr[z+1]->count <= 2)
            merge(parent,z-1,z);
    }
}

void Delete(int data){
    node* j = search(root,data);
    if(j == NULL){
        printf("The element is not found in the tree\n");
        return;
    }
    
    int x =0;
    for(i=0;i<j->count;i++){
        if(data == j->k[i])
            break;
        x++;
    }
    
    if(j->leaf == true){
        delete_leaf(j,x,data);
        return;
    }
    else{
        delete_nonleaf(j,x,data);
        return;
    }
}


int main()
{
    int choice;
    root = create_node();
    int data;
    node* t;
    while(1)
    {
        printf("\nchose an operation to perform\n");
        printf("1.Insert\n2.Delete\n3.Search\n4.Display\n5.Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter Num to  be inserted:\n");
                scanf("%d",&data);
                Insert(data);
                break;
            case 2:
                printf("Enter Num to be deleted:\n");
                scanf("%d",&data);
                Delete(data);
                break;
            case 3:
                printf("Enter Num to be searched:\n");
                scanf("%d",&data);
                t = search(root,data);
                if(t == NULL)
                    printf("Not found\n");
                else
                    printf("Found\n");
                break;
            case 4:
                printf("The elements in the tree are:\n");
                traverse(root) ;
                break;
            case 5:
                return 1;
            default:
                printf("Enter the correct choice\n");
        }
    }
}
