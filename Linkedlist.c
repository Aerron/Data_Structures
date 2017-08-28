#include <stdio.h>
#include <stdlib.h>

struct list_el
{
    int val;
    struct list_el * next;
}item_default={0,NULL}; //Default values
typedef struct list_el node;

node * head = NULL;

void insert_element(){
	int a;
	printf("Enter: ");
	scanf("%d", &a);
	
	node *linked = (node*)malloc(sizeof(node));
	linked->val = a;
	linked->next = head;
	head = linked;
}

void delete_element(){
	int a;
	printf("Enter: ");
	scanf("%d", &a);

	node * curr = head;
	node * curr1 = NULL;
	//delete all matched values
	while(curr != NULL ){
		if (curr->val == a)
		{
			if (curr == head)
			{
				head = head->next;
				free(curr);
				curr = head;
				/* code */
			}
			else{
				curr1->next = curr->next;
				free(curr);
				curr = curr1->next;
			}
		}
		else{
			curr1 = curr;
			curr = curr->next;
			
		}
	}
}


void display_elements(){
	node * curr = head;

	while (curr!=NULL )
	{
		printf(" %d -->", curr->val );
		curr = curr->next;
	}
	printf("\n");

}

int main(int argc, char const *argv[])
{
	
	int loop =1;

	while(loop == 1)
	{
		int choice;
		printf("Enter the choice 1-Insert, 2-Delete, 3-Display, 4-Stop\n");
		scanf("%d",&choice);
			switch(choice){
				case 1: 
					insert_element();
					break;
				case 2:
					delete_element();
					break;
				case 3:
					display_elements();
					break;
				case 4:
					loop = 0;
					break;
		}
	}

	
	
	return 0;
}












