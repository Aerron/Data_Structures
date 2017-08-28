#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct list_el
{
    int val;
    struct list_el * next;
}item_default={0,NULL}; //Default values
typedef struct list_el node;

node * head = NULL;


void enqueue(){
    int a;
    printf("Enter: ");
    scanf("%d",&a);
    
    
    node * linked = (node * )(malloc(sizeof(node)));
    linked->val = a;
    linked->next = head;
    head = linked;
}


int dequeue(){
    int a;
    if (head == NULL)
    {
        return INT_MIN;
        /* code */
    }
    else if ( head->next == NULL)
    {
        a = head->val;
        free(head);
        head = NULL;
        return a;
    }
   	else {
        node * curr = head;
        node * curr1 = NULL;
        while(curr->next != NULL){
            curr1 = curr;
            curr = curr->next;
        }
        a = curr->val;
        curr1->next = NULL;
        free(curr);
        return a;
        /* code */
    }
    
}


int main(int argc, char const *argv[])
{
    
    int a,loop =1;
    
    while(loop == 1)
    {
        int choice;
        printf("Enter the choice 1-Enqueue, 2-Dequeue, 3-stop\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                enqueue();
                break;
            case 2:
                a= dequeue();
                printf("%d\n",a );
                break;
            case 3:
                loop = 0;
                break;
        }
    }
    
    
    
    return 0;
}