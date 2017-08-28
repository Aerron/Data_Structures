#include <stdio.h>
#include <stdlib.h>


int top = -1, size;



void push(int Arr[]){
	int a;
	printf("Enter: ");
	scanf("%d",&a);

	if (top!=size-1)
	{
		Arr[++top] = a;
		/* code */
	}
}


int pop(int Arr[]){
	int a;
	a  = Arr[top--];
	return a;
	
}

void display_elements(int Arr[]){
	for (int i = 0; i <= top; ++i)
	{
		printf(" %d ", Arr[i]);
		/* code */
	}
}

int main(int argc, char const *argv[])
{
	int loop = 1;
	printf("Size: \n");
	scanf("%d",&size);

	int *Arr = (int *)malloc(size* sizeof(int));

	while(loop == 1)
	{
		int choice,a;
		printf("Enter the choice 1-Push, 2-Pop, 3-Display, 4-Stop\n");
		scanf("%d",&choice);
			switch(choice){
				case 1: 
					push(Arr);
					break;
				case 2:
					if (top!= -1){
						a = pop(Arr);
						printf("%d \n",a );
						}
					break;
				case 3:
					display_elements(Arr);
					break;
				case 4:
					loop = 0;
					break;
		}
	}
	return 0;
}