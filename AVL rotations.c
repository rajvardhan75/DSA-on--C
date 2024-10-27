#include <stdio.h>
#include <stdlib.h>
struct Node* root = NULL;

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int height(struct Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getBalance(struct Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

void preorderWithBalance(struct Node* root) {
    if (root != NULL) {
        printf("%d (Balance Factor: %d)\n", root->key, getBalance(root));
        preorderWithBalance(root->left);
        preorderWithBalance(root->right);
    }
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct Node* insert(struct Node* node, int key) {
    
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;  

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        printf("Before LL Rotation (Preorder with Balance Factors):\n");
        preorderWithBalance(root);
        printf("\n");
        node = rightRotate(node);
        printf("After LL Rotation (Preorder with Balance Factors):\n");
        preorderWithBalance(root);
        printf("\n");
        return node;
    }

    if (balance > 1 && key > node->left->key) {
        printf("Before LR Rotation (Preorder with Balance Factors):\n");
        preorderWithBalance(root);
        printf("\n");
        node->left = leftRotate(node->left);
        node = rightRotate(node);
        printf("After LR Rotation (Preorder with Balance Factors):\n");
        preorderWithBalance(root);
        printf("\n");
        return node;
    }

    if (balance < -1 && key > node->right->key) {
        printf("Before RR Rotation (Preorder with Balance Factors):\n");
        preorderWithBalance(root);
        printf("\n");
        node = leftRotate(node);
        printf("After RR Rotation (Preorder with Balance Factors):\n");
        preorderWithBalance(root);
        printf("\n");
        return node;
    }

    if (balance < -1 && key < node->right->key) {
        printf("Before RL Rotation (Preorder with Balance Factors):\n");
        preorderWithBalance(root);
        printf("\n");
        node->right = rightRotate(node->right);
        node = leftRotate(node);
        printf("After RL Rotation (Preorder with Balance Factors):\n");
        preorderWithBalance(root);
        printf("\n");
        return node;
    }

    return node;
}

int main() {
    int value;

    printf("Enter values to insert into the AVL tree (enter -1 to stop):\n");

    while (1) {
        scanf("%d", &value);
        if (value == -1) break;  

        printf("\nBefore inserting %d (Preorder with Balance Factors):\n", value);
        preorderWithBalance(root);
        printf("\n");

        root = insert(root, value);

        printf("\nAfter inserting %d (Preorder with Balance Factors):\n", value);
        preorderWithBalance(root);
        printf("\n");
    }

    return 0;
}
