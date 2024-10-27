#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct Stack {
    int top;
    int capacity;
    struct Node** array;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct Node* node) {
    if (isFull(stack)) return;
    stack->array[++stack->top] = node;
}

struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack)) return NULL;
    return stack->array[stack->top--];
}

struct Node* peek(struct Stack* stack) {
    return stack->array[stack->top];
}

struct Node* constructTree(char* postorder) {
    struct Stack* stack = createStack(strlen(postorder));
    struct Node* t,*t1,*t2;

    for (int i = 0; postorder[i] != '\0'; i++) {   
        if(isdigit(postorder[i])){
            t = newNode(postorder[i]);
            push(stack, t);
        } else {
            t = newNode(postorder[i]);
            t1 = pop(stack);
            t2 = pop(stack);
            t->right = t1;
            t->left = t2;
            printf("Node created has '%c'as root \n'%c' as left child \n'%c' as right child\n",t->data,t2->data,t1->data);
            push(stack,t);
        }
        printf("Stack Created:\n");
        for (int j = 0; j <= stack->top; j++) {
            printf("%c ", stack->array[j]->data);
        }
        printf("\n");
    }
    t = pop(stack);
    return t;
}

void inorder(struct Node* root) {
    if(root != NULL) {
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
    }
}

int evaluate(struct Node* root) {
    if (root->left == NULL && root->right == NULL)
        return root->data - '0';

    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    switch (root->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
    }
    return 0;
}

int main() {
    char postorderExpr[100];
    struct Node* root = NULL;
    printf("Enter the postorder expression: \n");
    scanf("%s", postorderExpr);
    root = constructTree(postorderExpr);
    printf("The inorder is: \n");
    inorder(root);
    printf("\nThe result of the expression is: %d\n", evaluate(root));
}
