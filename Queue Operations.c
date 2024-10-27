#include <stdio.h>
#define SIZE 5

int queue[SIZE], front = 0, rear = 0;

int isFull() {
    return (rear + 1) % SIZE == front;
}

int isEmpty() {
    return front == rear;
}

void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full!\n");
    } else {
        queue[rear] = value;
        rear = (rear + 1) % SIZE;
        printf("Inserted %d\n", value);
    }
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
    } else {
        printf("Deleted %d from position %d\n", queue[front], front);
        queue[front] = 0;  // Set dequeued position to 0
        front = (front + 1) % SIZE;
    }
}

void display() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
    } else {
        printf("Queue elements: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", queue[i]);
        }
        printf("\n");
        printf("Front is at position %d\n", front);
        printf("Rear is at position %d\n", rear);
    }
}

int main() {
    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
