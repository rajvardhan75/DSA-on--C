#include<stdio.h>
#define MAX 20


    int stack[MAX];
    int top = -1;

int push(int n){
    if(top == MAX - 1){
        printf("Stack is full\n");
    }
    else{
        top++;
        stack[top] = n;
        printf("Push %d\n",n);
    }

}
int pop(){
    if(top == -1){
        printf("Stack is empty\n");
    }
    else{
        int temp = stack[top];
        top--;
        return temp;
    }
}
int postfix(char* exp){
   
    int x,y;
    for(int i=0;exp[i]!='\0';i++){
        if(exp[i]>='0'&&exp[i]<='9'){
            push(exp[i] - '0');
          

        }
        else{
            x=pop();
            printf("Pop %d \n",x);
            y=pop();
            printf("Pop %d \n",y);
            switch(exp[i]){
                case '+':
                
                push(x+y);
                break;
                case '-':
                
                push(x-y);
                break;
                case  '*':
                
                push(x*y);
                break;
                case '/':
                
                push(x/y);
                break;

            }
        }

    }
    return pop();
}


int main(){

    char exp[MAX];
    printf("Enter the expression:");
    scanf("%s",exp);
    printf("Value of expression is: %d\n",postfix(exp));
    

}