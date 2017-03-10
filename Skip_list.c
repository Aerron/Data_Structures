/* C program for  implementation Skip  list */
//Name :- Amarnath
//Date modified :-  20/11/16
//
//  Created  on 16/08/16.
//  Copyright © 2016 . All rights reserved.
//




/*

top,start,top_end , last are the first and lst ones in the skip list

top,start contains INT_MIN 
top_end ,last contain INT_MAX

// the values are in the increasing order from left to right
top<->value1 -------------------------->top_end
 |                                         |                  
 V                                         v
top<->value1-----values---------------->top_end
 |      |          |                      |
 V      v          v                      v
top<->value1-----------values---------->top_end
 |      |                |                 |
 v      v                v                 v
top<->value1-----------------values---->top_end
 |      |                     |           |
 v      v                     v           v
start<->value1----------------values--->last

like wise everthing is connected all arrows means double directiong connected mutually

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// struct variable of each node
struct ele
{
    int value;
    struct ele *right,*left, *up,*down;
}node_default={0,NULL,NULL,NULL,NULL};// struct default values

// defining struct ele as node
typedef struct ele node;

// the max and min limits of skip list
node*start,*last, *top ,*top_end;

// defining no of levels and nodes to be 0 intially
int number_of_nodes = 0;
int number_of_levels = 0;

// function to generate numbers for coin flip
int ran(){
    time_t t;
    srand((unsigned) time(&t));
    return 1+(rand()%2);
}

// if the list is null then regenerate the new list that is all top,top_end,start,last are declared
void initialise (){
    // initialise the new skip list if the skip list doesn't exist that is number_of_nodes =0
    if(number_of_nodes==0){
        
        start=(node *)malloc(sizeof(node));
        last=(node *)malloc(sizeof(node));
        top=(node *)malloc(sizeof(node));
        top_end=(node *)malloc(sizeof(node));
        // connecting all the top, tope_end ,start,last and all other values to null
        /*
top,start contains INT_MIN 
top_end ,last contain INT_MAX
top and start are connected
top and top_end are connected
start and last are connected
last and top_end are connected
all other sides are taken as NULL by default in the struct

        */
        top->value= start->value= INT_MIN;
        top_end->value=last->value= INT_MAX;
        top_end->down=start->right = last;
        top_end->left = start->up = top;
        top->down=last->left = start;
        top->right =last->up = top_end;
        
    }
}



// to insert number into the skip list
void insert (int number){
    // initialise initialises the skip list if the skip list empty
    initialise();
    int loop=1; 
    // take a temp struct and intialise it with top 
    node *temp = top;
    // search function implemented similarly in delete 
    // start checking the skip list if the element entered is already present in the skip list
    do{
        // moving down the list to find the value
        if (temp->down != NULL) {
            temp = temp->down;
        }
        // if the value of the node is less then move to right
        while (temp->value<number) {
            temp = temp->right;
        }
        // if the entered number already exists in the list then return the value
        if (temp->value == number) {
            // return to user that the number already exists in the list
            printf("\nThe number: %d already exist\n",number);
            break;
        }
        // if the node value is greater than the inserted value then move back and go down and start checking it again 
        if (temp->value>number) {
            temp = temp->left;
        }
       // check until you reach the down most list to confirm that number doesn't exist in the list 
    }while (temp->down != NULL);
    
    // so now if the temp value isn't equal to the final value then start entering the value in the skip list
    if (temp->value != number) {
        // increase the number of nodes in the skip list
        number_of_nodes++;
        // create a new node for the inserting value
        node* newnode = (node *)malloc(sizeof(node));
        // now insert the value before temp
        /*



before 
                temp->top
                     ^
                     |
temp->left ------- temp---temp->right
                     |
                     v
                 temp->down

now insert newnode between temp left and temp

        */
        newnode->value = number;
        newnode->left = temp;
        newnode->right = temp->right;
        temp->right = newnode;
        newnode->right->left = newnode;
        newnode->down = NULL;
        newnode->up = NULL;

/*
                                  NULL       temp->top
                                   ^          ^
            present                |          |
temp->left(newnode->left) ---- newnode------ temp---temp->right
                                   |         |
                                   v         v
                                  NULL     temp->down
*/
        //normal insertion to the 0th row
        int temp_number_levels = 0;

/*


increasing the height of the new node by flipping the coin till the coin stops

*/
         // flip the coin and move the key up
        // do it till the coin gives the number other that 1 rand()==1 
        // loop to end the looping if it's reached the top most
        while ( ran() == 1 && loop==1) {
            // increase the 
            temp_number_levels++;
            if (number_of_levels<temp_number_levels)
            {
                number_of_levels = temp_number_levels;
                loop=0;
            }// if it grows behind the number of level increase the number of levels value
            
            // now connect the before and after values of new node as the node goes up
            node *temp_left = newnode->left;
            node *temp_right =newnode->right;
            // if the upper value of the left is null then go back till we get a node to connect 
            while (temp_left->up == NULL) {
                
                temp_left = temp_left->left;
            }
            // if the upper value of the right is null then go front till we get a node to connect 
            while (temp_right->up == NULL) {
                
                temp_right = temp_right->right;
            }
            // move the left one to it's upper node
            temp_left = temp_left->up;
            // move the right one to it's upper one
            temp_right = temp_right->up;
            // if the one at the left is top the create a new top to level up
            // lly new top_left to create a new top_left node to level up
            if (temp_left == top) {
                // dynamic memory for new level top and top end if it's the new level that doesn't have top and top end
                node *temp_top = (node *)malloc(sizeof(node));
                node *temp_top_end = (node *)malloc(sizeof(node));
                
                // now connecting the newnode of the new level to it's left and right 
                temp_top->up = NULL;
                temp_top->down = top ;
                // as the new levels top has a INT_MIN assigning its value
                temp_top->value = INT_MIN;
                // connecting it's left to NULL
                temp_top->left =  NULL;
                // connecting it's right to the new top_end and then inserting the new node at the bottom
                temp_top->right = temp_top_end;
                // connecting the old top to new top
                top->up = temp_top;
                // changing the top to new node
                top = temp_top;
                
                // lly for the top_end one assigning it's value as INT_MAX and all 
                temp_top_end->up = NULL;
                temp_top_end->down =top_end;
                temp_top_end->value = INT_MAX;
                temp_top_end->right = NULL;
                temp_top_end->left = top;
                top_end->up = temp_top_end;
                top_end = temp_top_end;
                
            }
            // creating a new node to insert in the new level 
            node* temp_newnode = (node *)malloc(sizeof(node));
            // assigning it's right,left,top,down,value
            temp_newnode->value = number;
            temp_newnode->left = temp_left;
            temp_newnode->right = temp_right;
            temp_left->right = temp_newnode;
            temp_right->left = temp_newnode;
            temp_newnode->down  = newnode;
            temp_newnode->up = NULL;
            newnode->up = temp_newnode;
            // moving the new node pointer to the newly inserted newnode for next step
            newnode = temp_newnode;
        }
    }
}


// delete the value in the skip list
void deletenumber(int number){
    node *temp2,*temp = top;
	// same as search in insert function
    // moving through all the values starting at the top and find the node where the value exists
    do{
        // moving to the right till the number is greater than the deleting one
        while (temp->value<number) {
            temp = temp->right;
        }
        // if number found break the loop and delete the value
        if (temp->value == number) {
            printf("The number %d exists \nDeleting the nunmber\n",number);
            break;
        }
        // if the number isn't found go to the left down
        if (temp->value>number) {
            temp = temp->left->down;
        }
        // loop until reach the bottom most level
    }while (temp != NULL);
    // if temp is NULL after the loop the element isn't found so return
    if (temp == NULL) {
        printf("The number %d doesn't exists \n",number);
        return;
    }
    // if the element is found then delete all the nodes of that values
    else{
        // delete all the nodes of that particular value till you reach the bottom most level
        while (temp!=NULL) {
			// if it's th only one in the horizontal coloumn of that element then just connect the top and top_end
            if (temp->left == top && temp->right == top_end) {
                top = top->down;
                top_end = top_end->down;
               	number_of_levels--;
            }
			// else connect the right one of the node to the left one 
            temp->left->right = temp->right;
            temp->right->left = temp->left;
            // note the value to free it
            temp2=temp;
            // move it to the down
            temp = temp->down;
            free(temp2);
        }
		// number_of_nodes must be decreased by 1
        number_of_nodes--;
    }
    
}

int search (int number){
    // go in the upper list and slowly come down
    node *temp = top;
    do{
        while (temp->value<number) {
			// horizontal check of the values till it reaches the number greater than that
            temp = temp->right;
        }
        if (temp->value == number) {
			// if found we can return
            printf("\nThe number: %d is found\n",number);
            return 1;
        }
        if (temp->value>number) {
			//go down if we didn't find the element in that level
            temp = temp->left->down;
        }
        // go until the bottom most level is reached
    }while (temp != NULL);
    // if the temp ends then element isn't found so return 0
    printf("\nNumber %d doesn't exist in the list\n",number);
    return 0;
}

int main() {
    
    int choice ,n;
    number_of_levels = 0;
    // prompt the user for choices
    printf("\nOperation codes are\n1)Insert\n2)Delete\n3)Search\n4)print skip list\n5)Height\n6)exit\n");
    while (1)
    {
        
        printf("\nEnter your choice : ");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1:
            // prompt the user the number to be inputted 
                printf("\nEnter the number to be inserted: ");
                scanf("%d",&n);
				// integer input and void reuturn
                insert(n);
                break;
            case 2:
            // ask the number to be deleted
                printf("\nEnter the number to be deleted:");
                scanf("%d",&n);
				// integer input and void reuturn
                deletenumber(n);
                break;
            case 3:
            // ask the number to be searched for
                printf("\nEnter the number that is to be searched: ");
                scanf("%d",&n);
				// integer input and void reuturn integer
                search(n);
                break;
            case 4:
            // if the number of nodes are not 0 then start printing 
                if(number_of_nodes!=0)
                {
                    printf("\nTotal number of elements in the list are = %d\n",number_of_nodes);
                    printf("\nThe numbers in ascending order are :   ");
                    // print all the values in the bottom row starting from the element right to the start
                    node*temp = start->right;
                    // print until the last node is reached
                    while(temp!= last){
                        // print the value
                        printf("%d\t",temp->value);
                        temp = temp->right;
                    }
                    printf("\n\n");
                }
                // if skip list is empty else is runned
                else
                    printf("\nSkip list is empty!!\n");
                break;
            case 5:
            // to print the number of levels
                printf("\nThe levels in the skip list are : %d\n",number_of_levels);
                break;
            case 6:
            // abort the program
                exit(1);
                break;
            default:
                printf("\nWrong Choice\n");
        }
    }
    
}
