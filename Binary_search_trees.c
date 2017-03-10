/* C program for  implementation Binary search tree */
//Name :- Amarnath
//Date modified :-  20/11/16.
//
//  Created  on 10/11/16.
//  Copyright © 2016 . All rights reserved.
//


#include <string.h>
#include <stdio.h>
#include <stdlib.h>



struct item
{
    int val;
    struct item  * right, * left,*parent;
}node_default={0,NULL,NULL,NULL};
// defining default struct

//global declaration
typedef struct item node;
node * root;

// Insert the element in the binary
node * insert (int v)
{
    node *temp = (struct item *) malloc(sizeof(node));
    //Root case
    if (root==NULL)
    {
        root      = temp;
        root->val = v;
        root->left=root->right=NULL;
        return root;
    }
    // leaf insertion
    else
    {
        //  node x to flow through the list to check
        node * x=root;
        while (x!=NULL)
        {
            // right is takes as greater than or equal to
            if (x->val >= v )
            {
                if (x->left == NULL)
                {
                    // if we find the leaf insert there
                    x->left = temp;
                    temp -> val = v;
                    temp->parent=x;
                    temp->right=temp->left=NULL;
                    return temp;
                    // returning the entered address
                }
                // moving to the next pointer if it's not a leaf
                x= x-> left;
                
            }
            else
            {
                if (x->right == NULL)
                {
                    // if we find the leaf insert there
                    x->right = temp;
                    temp -> val = v;
                    temp->parent=x;
                    temp->right=temp->left=NULL;
                    return temp;
                }
                // moving to the next pointer
                x = x->right;
            }
        }
        
    }
    
    return NULL;
}

// search the element in the tree by starting from the root
node * search(int s)
{
    node * temp;
    temp = root;
    // if root doesn't exist there is no tree
    if (root==NULL)
    {
        return NULL ;
        // return nothing as empty leaf doens't have anything
    }
    // loop till it reaches some leaf
    while( temp != NULL)
    {
        // if found return the node*
        if (temp ->val==s)
        {
            return temp;
        }
        // else keep on going till u find leaf and then stop
        else if (temp->val < s)
        {
            temp = temp -> right;
        }
        else
        {
            temp = temp -> left;
        }
    }
    return NULL;
    
}

// Deleting the element in the tree
void delet(int r)
{
    node*temp=root;
    node*temp2 = NULL,*temp3=NULL,*temp4=NULL,*d=NULL;
    int f=0,p;
    
    // deleting the root case
    if(root->val==r)
    {
        // both the roots are empty
        if(root->left==NULL && root->right==NULL)
        {
            d=root;
            // tree vanishes
            root=NULL;
            printf("\nElement deleted\n");
            free(d);//delete the element
            return;
        }
        //if right isn't empty
        else if(root->left==NULL && root->right!=NULL)
        {
            d=root;
            // change the root to the final variable
            root=root->right;
            printf("\nElement deleted\n");
            free(d);
            return;
        }
        //if left isn't empty
        else if(root->left!=NULL && root->right==NULL)
        {
            d=root;
            // change the root to left
            root=root->left;
            printf("\nElement deleted\n");
            free(d);
            return;
        }
        
        
    }
    // move till the end
    while(temp!=NULL)
    {
        // if matched beak the loop
        if(temp->val==r)
        {
            f=1;
            break;
        }
        // else go to next one till you find it or end the list
        else if(temp->val<r)
        {
            temp2=temp;
            temp=temp->right;
        }
        else
        {
            temp2=temp;
            temp=temp->left;
        }
    }
    // if counter f=0 then no elements found
    if(f==0)
    {
        printf("The  given value doesn't exist\n");
        return;
    }
    // if any element found
    
    // If it's a leaf node
    else if((temp->right==NULL)&&(temp->left==NULL))
    {
        // detach the node from the parent
        if(temp2->val<r)
        {
            temp2->right=NULL;
        }
        else
        {
            temp2->left=NULL;
        }
        // deallocate the memory
        free(temp);
        return;
    }
    // if it has one child and is left
    else if(temp->right==NULL)
    {
        // find the parent that need to deleted from
        if(temp2->val<r)
        {
            temp2->right=temp->left;
        }
        else
        {
            temp2->left=temp->left;
        }
        free(temp);
        return;
    }
    // if it has one child and is right
    else if(temp->left==NULL)
    {
        // point temp2 right to the right one of temp
        if(temp2->val<r)
        {
            temp2->right=temp->right;
        }
        // point temp2 left to the right one of temp
        else
        {
            temp2->left=temp->right;
        }
        free(temp);
        return;
    }
    // if it has both child then find the values that can be transfered
    else
    {
        // loop it and find the appropriate value to be replaced it
        temp4=temp;
        temp3=temp->right;
        while(temp3->left!=NULL)
        {
            temp4=temp3;
            temp3=temp3->left;
        }
        p=temp3->val;
        // if both are null
        if((temp3->right==NULL)&&(temp3->left==NULL))
        {
            if(temp4->val<p)
            {
                temp4->right=NULL;
            }
            else
            {
                temp4->left=NULL;
            }
            free(temp3);
        }
        // only left is null
        else if(temp3->left==NULL)
        {
            if(temp4->val<p)
            {
                temp4->right=temp3->right;
            }
            else
            {
                temp4->left=temp3->right;
            }
            free(temp3);
        }
        temp->val=p;
    }
    
}



void inorder(node* temp)
{
    if(temp==NULL)
    {
        return;
    }
    if(temp->left!=NULL)
    {
    inorder(temp->left);
    }
    printf(" %d \n", temp -> val  );
    if(temp->right!=NULL)
    {
    inorder(temp -> right );
    }
    return ;
}


void pre_order(node* temp)
{
    if(temp==NULL)
    {
        return;
    }
    printf(" %d \n", temp -> val  );
    if(temp->left!=NULL)
    {
    pre_order(temp->left);
    }
    if(temp->right!=NULL)
    {
    pre_order(temp -> right );
    }
    return ;
}

void post_order(node* temp)
{
    if(temp==NULL)
    {
        return;
    }
    if(temp->left!=NULL)
    {
    post_order(temp->left);
    }
    if(temp->right!=NULL)
    {
    post_order(temp -> right );
    }
    printf(" %d \n", temp -> val  );
    return ;
}

// Displays the preorder
void display(node* temp)
{
    printf("\nInorder\n");
    inorder(temp);
    printf("\nPreorder\n");
    pre_order(temp);
    printf("\nPostorder\n");
    post_order(temp);
    
}

int main(int argc, char const *argv[])
{
    int x,c;
    node * temp;
    // loop for input from the variable
    
    while (1)
    {
        // options of insert
        printf("\n1)Insert \n2)Delete \n3)Search \n4)Display \n5)Exit\nPlease enter an integer(1-5): ");
        scanf("%d",&c);
            switch(c)
        {
            case 1:
                printf("\nEnter the element to be entered into the tree : \n");
                scanf("%d",&x);
                // pass integer type to the insert and it returns the integer type
                temp = insert(x);
                // calling the display after every insert
                display(root);
                printf("\n%d is inserted at address %p . \n",x,temp );
                break;
            case 2:
                if(root==NULL)
                {
                    printf("No tree exist");
                    break;
                }
                printf("\nEnter the element to be deleted : \n");
                scanf("%d",&x);
                // deleting the element if the element exists in the tree
                delet(x);
                display(root);
                break;
            case 3:
                if(root==NULL)
                {
                    printf("No tree exist");
                    break;
                }
                printf("\nEnter the element to be Searched : \n");
                scanf("%d",&x);
                temp = search(x);
                if (temp==NULL)
                {
                    printf("\nNO such element found \n");
                }
                else
                    printf("\n%d is found at %p \n",x,temp );
                break ;
            case 4:
                if(root==NULL)
                {
                    printf("No tree exist");
                    break;
                }
                display(root);
                break;
            case 5:
                // out from the tree
                abort();
                break;
            default:
                printf("\nEnter the correct choice\n");
                break;
                
        }
        
        
    }
    return 0;
}
