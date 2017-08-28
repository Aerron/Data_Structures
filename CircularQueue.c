#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int front=0, rear=-1, size;

void enqueue(int Arr[]){
    int a;
    printf("Enter: ");
    scanf("%d",&a);
    
    if( !( (front==0&&rear==size-1) || (front>0&&rear==front-1) ) ){
        rear = (rear+1)%size;
        Arr[rear] = a;
    }
    
}


int dequeue(int Arr[]){
    int a = INT_MIN;
    
    if (front == rear)
    {
        a = Arr[front];
        front = 0;
        rear = -1;
    }
    else if(!(front==0&&rear==-1)){
        a = Arr[front];
        front = (front +1) % size;
    }
    return a;
    
}

void display_elements(int Arr[]){
    if (!(front==0&&rear==-1))
    {
        int diff = (rear-front+1+size)%size, i = front;
        if (diff == 0) {
            diff = size;
        }
        printf("%d\n", diff);
        while(diff > 0){
            printf("%d  ",Arr[i] );
            i = (i+1) %size;
            diff--;
        }
    }
}

int main(int argc, char const *argv[])
{
    int loop = 1;
    printf("Size: \n");
    scanf("%d",&size);
    
    int * Arr = (int *) (malloc(size*sizeof(int)));
    
    
    while(loop == 1)
    {
        int choice,a;
        printf("Enter the choice 1-Enqueue, 2-Dequeue, 3-Display, 4-Stop\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                enqueue(Arr);
                break;
            case 2:
                a = dequeue(Arr);
                printf("%d\n", a);
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