#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPTH 4

typedef struct node {
    int datum;
    char pos[5];
    struct node *left;
    struct node *right;
} Node;

void insert(Node **root, int datum);
void delete(Node **root, int datum);
Node *leftMost(Node *root);
void setPos(Node *root, char *step);
void clear(Node **root);
void print(Node *root, int color);

int main(void) {
    Node *r = NULL;
    insert(&r, 5);
    insert(&r, 4);
    insert(&r, 3);
    insert(&r, 6);
    insert(&r, 79);
    insert(&r, 99);
    insert(&r, 16);
    insert(&r, 100);
    setPos(r, "\0");
    print(r, 31);
    clear(&r);
    return 0;
}

void insert(Node **root, int datum) {
    static int depth = 0;
    Node *tree = *root;
    if(depth > MAX_DEPTH) {
        printf("%d could not be inserted because doing so would make the tree greater than the maximum possible depth\n", datum);
        return;
    }
    if(!tree) {
        *root = malloc(sizeof(Node));
        tree = *root;
        tree->pos[0] = '\0';
        tree->left = NULL;
        tree->right = NULL;
        tree->datum = datum;
        return;
    }
    if(tree->datum > datum) {
        depth++;
        insert(&(tree->left), datum);
        depth--;
        return;
    } else {
        depth++;
        insert(&(tree->right), datum);
        depth--;
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

void setPos(Node *root, char *step) {
    if(!root)
        return;
    size_t x;
    strcpy(root->pos, step);
    char l[5], r[5];
    for(x = 0; step[x] != '\0'; x++)
        l[x] = step[x];
    l[x] = 'l';
    l[x + 1] = '\0';
    for(x = 0; step[x] != '\0'; x++)
        r[x] = step[x];
    r[x] = 'r';
    r[x + 1] = '\0';
    setPos(root->left, l);
    setPos(root->right, r);
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

void print(Node *root, int color) {
    //red: 31   green: 32   blue: 34
    static int depth = 0;
    if(!root)
        return;
    depth++;
    print(root->right, color);
    depth--;
    for(int x = 0; x < depth; x++)
        printf("  ");
    printf("\x1b[%dm%d:%s\x1b[0m\n", color, root->datum, root->pos);
    depth++;
    print(root->left, color);
    depth--;
}