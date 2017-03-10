// Implementation of redblack trees
//Name :- Amarnath
//Date modified :-  20/11/16
//
//  Created  on 14/11/16.
//  Copyright © 2016 . All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// create struct for node
//1 -> Black
//0 -> Red
struct list_el
{
    int data;
    int color;
    struct list_el * left;
    struct list_el * right;
    struct list_el * parent;
    
};//colour by default

typedef struct list_el node;

// root for the top one
node * root,*N;

/*When we do a left rotation on a node x,
 we assume that its right child y is not T;
  x may be any node in the tree whose right child is not T*/

/* It makes y the new root of the subtree, 
with x as y’s left child and y’s left child as x’s right child.*/
void left_rotate(node * x)
{
    node * right_ele = N;
    
    right_ele=x->right;
    x->right=right_ele->left;
    if(right_ele->left!=N)
    {
        right_ele->left->parent=x;
    }
    right_ele->parent=x->parent;
    if(x->parent==N)
    {
        root=right_ele;
    }
    else if(x==x->parent->left)
    {
        x->parent->left=right_ele;
    }
    else
        x->parent->right=right_ele;
    right_ele->left=x;
    x->parent=right_ele;
    
    
}


/*When we do a right rotation on a node x, we assume that its 
left child y is not T; x may be any node in the tree 
whose left child is not T*/


/* It makes y the new root of the subtree,
 with x as y’s right child and y’s right child 
 as x’s left child.*/

void right_rotate(node * x)
{
    node * left_ele = N;
    left_ele=x->left;
    x->left=left_ele->right;
    if(left_ele->right!=N)
    {
        left_ele->right->parent=x;
    }
    left_ele->parent=x->parent;
    if(x->parent==N)
    {
        root=left_ele;
    }
    else if(x==x->parent->right)
    {
        x->parent->right=left_ele;
    }
    else
        x->parent->left=left_ele;
    left_ele->right=x;
    x->parent=left_ele;
    
}


// to fix the rb tree violations
void insert_fixed(node *item)
{
    node * uncle=N;
    // if it's not a root and violating the rb conditions
    while( item->parent->color==0)
    {
        
        if (item->parent==item->parent->parent->left)
        {
            uncle=item->parent->parent->right;
            // if uncle is red
            if (uncle->color==0 )
            {
                //Because  item:p:p is black, we can color both  item:p and y black, 
                //thereby fixing the problem of  item and  item:p both being red, and 
                //we can color  item:p:p red, thereby maintaining property
                uncle->color=item->parent->color=1;
                item->parent->parent->color=0;
                item=item->parent->parent;
                
            }
            else
            {
                // checking if it's a right child
                if(item==item->parent->right)
                {
                    item=item->parent;
                    left_rotate(item);
                }
                // checking if it's a left child
                else
                {
                    item->parent->color=1;
                    item->parent->parent->color=0;
                    right_rotate(item->parent->parent);
                }
            }
            
        }
        else
        {
            uncle=item->parent->parent->left;
            // if uncle is red
            if (uncle->color==0 )
            {
                /*Because  item:p:p is black, we can color both  
                item:p and y black, thereby fixing the problem of  item and  item:p 
                both being red, and we can color  item:p:p red, thereby maintaining property*/
                item->parent->color=uncle->color=1;
                item->parent->parent->color=0;
                item=item->parent->parent;
                
            }
            else
            {
                // checking if it's a left child
                if(item==item->parent->left)
                {
                    item=item->parent;
                    right_rotate(item);
                }
                // checking if it's a right child
                else
                {
                    item->parent->color=1;
                    item->parent->parent->color=0;
                    left_rotate(item->parent->parent);
                }
            }
        }
    }
    // make the root black as it may become red in case of red transfer to the grand parent
    root->color=1;
    return;
}

// normal insert as binary search tree
void insert_ele(int r)
{
    node * temp = (node *)malloc(sizeof (node));
    node *temp2,*temp3;
    //Stroing the input key in temp
    temp->data=r;
    temp->right=temp->left=N;
    temp->color=0;
    
    temp2=root;
    temp3=N;
    
    while(temp2!=N) //Chenking if root is NULL
    {
        temp3=temp2;
        if(temp2->data<r)
            temp2=temp2->right;
        else
            temp2=temp2->left;
    }
    temp->parent =temp3;
    //Case when only the element being inserted is in the tree
    if(temp3==N)
        root=temp;
    //Navigating to left/right according to the value
    else if(temp3->data<r)
        temp3->right=temp;
    else
        temp3->left=temp;
    //coloring  temp as red may cause a violation of one of the red-black properties, we call insert_fixed
    insert_fixed(temp);
}


node * search_ele(int s)
{
    node * temp;
    temp = root;
    // if tree doesn't eists return null
    if (root==N)
    {
        return N ;
        
    }
    // loop till the last
    while( temp != N)
    {
        if (temp ->data==s)
        {
            // return the found pointer node
            return temp;
        }
        else if (temp->data < s)
        {
            // go right for val<s
            temp = temp -> right;
        }
        else
        {
            // go left for val>=s
            temp = temp -> left;
        }
    }
    // if not found return Null
    return N;
    
}

// preorder
void display(node* temp)
{
    if(temp == N)
    {
        return;
    }
    
    display(temp->left);
    printf(" %d ---- %d\n", temp -> data, temp-> color  );
    display(temp -> right );
}

//to move subtrees around within the rb tree, we define a subroutine TRANSPLANT, 
//which replaces one subtree as a child of its parent with another subtree
void RedBlackTransplant(node *u,node *v)
{
    if (u->parent==N)
    {
        root=v;
    }
    else if (u==u->parent->left)
    {
        u->parent->left=v;
    }
    else
        u->parent->right=v;
    v->parent=u->parent;
    
}

//To find the node with least key
node * TreeMinimum(node *u)
{
    while(u->left!=N)
    {
        u=u->left;
    }
    return u;
}

//To fix rb tree properties if violated by delete
void RemoveFixed(node *x)
{
    node *w;
    while(x!=root && x->color==1)
    {
        if (x==x->parent->left)
        {
            w=x->parent->right;
            if (w->color==0)
            {
                // x’s sibling w is red
                w->color=1;
                x->parent->color=0;
                left_rotate(x->parent);
                w=x->parent->right;
            }
            if (w->left->color==1 && w->right->color==1)
            {
                // x’s sibling w is black, and both of w’s children are black
                w->color=0;
                x=x->parent;
            }
            else
            {
                if (w->right->color==1)
                {
                    //x’s sibling w is black, w’s left child is red, and w’s right child is black
                    w->left->color=1;
                    w->color=0;
                    right_rotate(w);
                    w=x->parent->right;
                }
                else{
                    //x’s sibling w is black, and w’s right child is red
                    w->color=x->parent->color;
                    x->parent->color=1;
                    w->right->color=1;
                    left_rotate(x->parent);
                    x=root;
                }
            }
        }
        else
        {
            w=(x->parent)->left;
            if (w->color==0)
            {
                // x’s sibling w is red
                //Since w must have black children, we can switch the colors of w and x->p 
                //and then perform a left-rotation on x->p without violating any of the red-black properties. 
                //The new sibling of x, which is one of w’s children prior to the rotation, is now black
                w->color=1;
                (x->parent)->color=0;
                right_rotate(x->parent);
                w=x->parent->left;
            }
            if (w->right->color==1 && w->left->color==1)
            {
                // x’s sibling w is black, and both of w’s children are black
                w->color=0;
                x=x->parent;
            }
            else
            {
                if (w->left->color==1)
                {
                    //x’s sibling w is black, w’s left child is red, and w’s right child is black
                    w->right->color=1;
                    w->color=0;
                    left_rotate(w);
                    w=x->parent->left;
                }
                else{
                    //x’s sibling w is black, and w’s right child is red
                    w->color=x->parent->color;
                    x->parent->color=1;
                    w->left->color=1;
                    right_rotate(x->parent);
                    x=root;
                }
            }
        }
    }
    x->color=1;
}

void rb_delete(node * z)
{
    //We maintain node y as the node either removed from the tree or moved within the tree
    node * y,*x;
    y=z;
    //Because node y’s color might change, the variable colour stores y’s color before any changes occur
    int colour=y->color;
    //when z has fewer than two children then it is removed directly
    if (z->left==N)
    {
        x=z->right;
        RedBlackTransplant(z,z->right);
    }
    else if (z->right==N)
    {
        x=z->left;
        RedBlackTransplant(z,z->left);
    }
    else
    {
        //When z has two children, then y!=z and node y moves into node z's original position in the red-black tree
        y=TreeMinimum (z->right);
        //We need to save y’s original color in order to test it at the end of RB-DELETE; 
        //if it was black, then removing or moving y could cause violations of the red-black properties.
        colour=y->color;
        x=y->right;
        if (y->parent==z)
        {
            x->parent=y;
        }
        else
        {
            RedBlackTransplant(y,y->right);
            y->right=z->right;
            (y->right)->parent=y;
        }
        RedBlackTransplant(z,y);
        y->left=z->left;
        (y->left)->parent=y;
        y->color=z->color;
    }
    //Finally, if node y was black, we might have introduced one or more 
    //violations of the red-black properties, and so we call RemoveFixed
    if (colour==1)
    {
        RemoveFixed(x);
    }
    
}
int main()
{
    int x_enter,c;
    node * temp;
    N=(node *)malloc(sizeof(node));
    N->parent=N->left=N->right=NULL;
    N->color=1;
    root=N;
    while (1)
    {
        // Prompt user
        printf("\n1)Insert \n2)Delete \n3)Display \n4)Search \n5)Exit\nEnter the choice : ");
        scanf("%d",&c);
        // for wrong choice
        if (c>5||c<1)
        {
            printf("Enter the correct choice !!!\n");
            
        }
        else
            switch(c)
        {
            case 1:
                // insertion
                printf("\nEnter the element to be entered into the tree : \n");
                scanf("%d",&x_enter);
                insert_ele(x_enter);
                display(root);
                break;
            case 2:
                // deletion
                printf("\nEnter the element to be deleted : \n");
                scanf("%d",&x_enter);
                temp=search_ele(x_enter);
                if(temp!=N)
                {
                    rb_delete(temp);
                    display(root);
                }
                else
                    printf("\nThere doesn't exist the number given in the list\n");
                break;
            case 3:
                //Displaying the tree
                display(root);
                break;
            case 4:
                //Searching for an element
                printf("\nEnter the element to be searched : \n");
                scanf("%d",&x_enter);
                temp=search_ele(x_enter);
                if(temp!=N)
                {
                    if(temp->color ==1)
                    {
                        //Displaying with colour
                        printf("\n%d is found at address %p with colour BLACK. \n",x_enter,temp);
                    }
                    else

                        printf("\n%d is found at address %p with colour RED . \n",x_enter,temp);
                }
                else
                    printf("\nThere doesn't exist the number given in the list\n");
                break;
            case 5:
                // Stop the program
                exit(1);
                break;
                
        }
        
        
    }
    return 0;
}
// Referred cormen Introduction to algorithms
