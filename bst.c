#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int datum;
    struct node *left;
    struct node *right;
} Node;

void insert(Node **root, int datum);
void delete(Node **root, int datum);
Node *leftMost(Node *root);
void clear(Node **root);
void print(Node *root);

int main(void) {
    Node *r = NULL;
    insert(&r, 5);
    insert(&r, 4);
    insert(&r, 3);
    insert(&r, 6);
    delete(&r, 5);
    print(r);
    clear(&r);
    return 0;
}

void insert(Node **root, int datum) {
    Node *tree = *root;
    if(!tree) {
        *root = malloc(sizeof(Node));
        tree = *root;
        tree->left = NULL;
        tree->right = NULL;
        tree->datum = datum;
        return;
    }
    if(tree->datum > datum) {
        insert(&(tree->left), datum);
        return;
    } else {
        insert(&(tree->right), datum);
    }
}

void delete(Node **root, int datum) {
    Node *tree = *root;
    if(!tree) {
        printf("%d not found in tree\n", datum);
        return;
    }
    if(datum < tree->datum) {
        delete(&(tree->left), datum);
        return;
    }
    if(datum > tree->datum) {
        delete(&(tree->right), datum);
        return;
    }
    if(tree->left && tree->right) {
        Node *newNode = leftMost(tree->right);
        tree->datum = newNode->datum;
        delete(&(tree->right), newNode->datum);
        return;
    }
    if(!tree->left)
        *root = tree->right;
    else
        *root = tree->left;
    free(tree);
}

Node *leftMost(Node *root) {
    if(!root->left)
        return root;
    return leftMost(root->left);
}

void clear(Node **root) {
    Node *node = *root;
    if(!node)
        return;
    clear(&(node->left));
    clear(&(node->right));
    free(node);
    *root = NULL;
}

void print(Node *root) {
    static int depth = 0;
    if(!root)
        return;
    depth++;
    print(root->right);
    depth--;
    for(int x = 0; x < depth; x++)
        printf("  ");
    printf("%d\n", root->datum);
    depth++;
    print(root->left);
    depth--;
}