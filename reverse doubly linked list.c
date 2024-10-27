#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* next;
    struct node* prev;
};

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void append(struct node** head, int data) {
    struct node* newNode = createNode(data);
    struct node* temp = *head;
   
    if (*head == NULL) {
        *head = newNode;
        return;
    }


    while (temp->next != NULL) {
        temp = temp->next;
    }
   
   
    temp->next = newNode;
    newNode->prev = temp;
   
}

void printList(struct node* node) {
    while (node != NULL) {
        printf("%d <->", node->data);
        node = node->next;
    }
    printf("NULL");
    printf("\n");
}

void reverseList(struct node** head) {
    struct node* temp = NULL;
    struct node* current = *head;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL) {
        *head = temp->prev;
    }
}

int main() {
    struct node* head = NULL;
    int choice, data;

    while (1) {
        printf("\n1. Append element to the list\n");
        printf("2. Print initial list\n");
        printf("3. Print reversed list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
            printf("Enter the number: ");
            scanf("%d",&data);
            append(&head,data);
            break;

            case 2:
            printf("Original list: \n");
            printList(head);
            break;

            case 3:
            printf("Reversed list: \n");
            reverseList(&head);
            printList(head);
            break;

            case 4:
            exit(0);
            break;

        }

    }
}