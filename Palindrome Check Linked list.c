#include<stdio.h>
#include<stdlib.h>

struct Node {
    int val;
    struct Node *next;
};

struct Node* reverseList(struct Node* head) {
    struct Node* previous = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}

int isPalindrome(struct Node* head) {
    if (head == NULL || head->next == NULL) return 1;

    struct Node *slow = head, *fast = head, *firstHalf = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    struct Node* secondHalf = reverseList(slow);
    struct Node* temp = secondHalf;

    int result = 1;
    while (temp != NULL) {
        if (firstHalf->val != temp->val) {
            result = 0;
            break;;
        }
        firstHalf = firstHalf->next;
        temp = temp->next;
    }

    struct Node* previous = NULL;
    struct Node* current = secondHalf;
    while (current != NULL) {
        struct Node* next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    free(secondHalf);
    return result;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->val);
       current = current->next;
    }
    printf("NULL\n");
}

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    struct Node* last = *head;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

void printReversed(struct Node** head) {
    *head = reverseList(*head);
    printf("Reversed list: ");
    printList(*head);
    *head = reverseList(*head);
}

int main() {
    struct Node* head = NULL;

    int n;
    printf("Enter length: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int value;
        printf("Enter the value of %d: ", i + 1);
        scanf("%d", &value);
        appendNode(&head, value);
    }

    printf("Original list: ");
    printList(head);

    printReversed(&head);

    if (isPalindrome (head))
        printf("Linked list is a palindrome.\n");
    else
        printf("Linked list is not a palindrome.\n");


    return 0;
}