#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DEPTH 4
#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255
#define DELAY_SECONDS 0
#define DELAY_NANOSECONDS 250000000

typedef struct node {
    int datum;
    int height;
    int bal;
    char pos[MAX_DEPTH + 1];
    struct node *parent;
    struct node *left;
    struct node *right;
} Node;

typedef struct vector {
    size_t capacity;
    size_t size;
    int *data;
} Vector;

enum Color {RED = 31, GREEN = 32, BLUE = 34};

int maxHeight(Node *node);
int balance(Node *node);
void balanceTree(Node *node);
void balanceTreeS2(Node *root);
void rotateLeft(Node **node);
void rotateRight(Node **node);
void insert(Node **tree, int datum);
void insertBST(Node **tree, Node *node);
void delete(Node **root, int datum);
Node *leftMost(Node *root);
void rebalance(Node **tree);
void clear(Node **root);
void print(Node *root, enum Color color);
void setPos(Node *root, char *step);
void writeTree(char *filename, Node *root);
void writeNode(FILE *fptr, Node *node);
void randomize(enum Color color, Node **root, Vector *vector);
void initVector(Vector *vector);
void appendVector(Vector *vector, int datum);
void deleteVector(Vector *vector, int datum);
void clearVector(Vector *vector);

int main(void) {
    Node *r = NULL;
    Node *g = NULL;
    Node *b = NULL;
    Vector red, green, blue;
    initVector(&red);
    initVector(&green);
    initVector(&blue);
    srand(time(NULL));
    struct timespec delay, delay2;
    delay.tv_sec = DELAY_SECONDS;
    delay.tv_nsec = DELAY_NANOSECONDS;
    while(1) {
        int treeToEdit = rand() % 3;
        switch(treeToEdit) {
            case 0:
                randomize(RED, &r, &red);
                break;
            case 1:
                randomize(GREEN, &g, &green);
                break;
            default:
                randomize(BLUE, &b, &blue);
                break;
        }
        nanosleep(&delay, &delay2);
    }
    return 0;
}

int maxHeight(Node *node) {
    int l = -1, r = -1;
    if(node->left)
        l = node->left->height;
    if(node->right)
        r = node->right->height;
    return l > r? l : r;
}

int balance(Node *node) {
    int l = -1, r = -1;
    if(node->left)
        l = node->left->height;
    if(node->right)
        r = node->right->height;
    printf("bal: %d\n", l - r);
    return l - r;
}

void balanceTree(Node *node) {
    Node *curr = node->parent? node->parent: node;
    while(curr->parent)
        curr = curr->parent;
    balanceTreeS2(curr);
}

void balanceTreeS2(Node *root) {
    if(!root)
        return;
    if(!root->left && !root->right) {
        root->bal = 0;
        return;
    }
    int l = -1, r = -1;
    if(root->left) {
        l = root->left->height;
        balanceTreeS2(root->left);
    }
    if(root->right) {
        r = root->right->height;
        balanceTreeS2(root->right);
    }
    root->bal = l - r;
}

void rotateLeft(Node **node) {
    Node *oldRoot = *node;
    Node *newRoot = oldRoot->right;
    oldRoot->right = newRoot->left? newRoot->left: NULL;
    if(oldRoot->right)
        oldRoot->right->parent = oldRoot;
    newRoot->left = oldRoot;
    oldRoot->height = 1 + maxHeight(oldRoot);
    newRoot->height = 1 + maxHeight(oldRoot);

    if(oldRoot->parent) {
        Node *g = oldRoot->parent;
        newRoot->parent = oldRoot->parent;
        if(newRoot->datum < g->datum)
            g->left = newRoot;
        else
            g->right = newRoot;
    } else
        newRoot->parent = NULL;
    oldRoot->parent = newRoot;
    *node = newRoot;
}

void rotateRight(Node **node) {
    Node *oldRoot = *node;
    Node *newRoot = oldRoot->left;
    oldRoot->left = newRoot->right? newRoot->right: NULL;
    if(oldRoot->left)
        oldRoot->left->parent = oldRoot;
    newRoot->right = oldRoot;
    oldRoot->height = 1 + maxHeight(oldRoot);
    newRoot->height = 1 + maxHeight(newRoot);

    if(oldRoot->parent) {
        Node *g = oldRoot->parent;
        newRoot->parent = oldRoot->parent;
        if(newRoot->datum < g->datum)
            g->left = newRoot;
        else
            g->right = newRoot;
    } else
        newRoot->parent = NULL;
    oldRoot->parent = newRoot;
    *node = newRoot;
}

void insert(Node **tree, int datum) {
    Node *newNode = malloc(sizeof(Node));
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->datum = datum;
    newNode->height = 0;
    insertBST(tree, newNode);
    while(newNode->parent)
        newNode = newNode->parent;
    *tree = newNode;
}

void insertBST(Node **tree, Node *node) {
    static int depth = 0;
    if(depth > MAX_DEPTH) {
        printf("%d could not be inserted because doing so would make the tree greater than the maximum possible depth\n\n", node->datum);
        return;
    }
    if(*tree && node->datum < (*tree)->datum) {
        if((*tree)->left) {
            depth++;
            insertBST(&(*tree)->left, node);
            depth--;
            (*tree)->height = 1 + maxHeight(*tree);
            balanceTree(*tree);
            rebalance(tree);
            return;
        } else {
            (*tree)->left = node;
            (*tree)->height = 1 + maxHeight(*tree);
            balanceTree(*tree);
            rebalance(tree);
        }
    } else if(*tree && node->datum > (*tree)->datum) {
        if((*tree)->right) {
            depth++;
            insertBST(&(*tree)->right, node);
            depth--;
            (*tree)->height = 1 + maxHeight(*tree);
            balanceTree(*tree);
            rebalance(tree);
            return;
        } else {
            (*tree)->right = node;
            (*tree)->height = 1 + maxHeight(*tree);
            balanceTree(*tree);
            rebalance(tree);
        }
    }
    node->parent = *tree;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
}

void delete(Node **root, int datum) {
    Node *tmp = *root;
    if(!tmp) {
        printf("%d not found in tree\n", datum);
        return;
    }
    if(datum < tmp->datum) {
        delete(&(tmp->left), datum);
        (*root)->height = 1 + maxHeight(*root);
        balanceTree(*root);
        rebalance(root);
        return;
    }
    if(datum > tmp->datum) {
        delete(&(tmp->right), datum);
        (*root)->height = 1 + maxHeight(*root);
        balanceTree(*root);
        rebalance(root);
        return;
    }
    if(tmp->left && tmp->right) {
        Node *next = leftMost(tmp->right);
        tmp->datum = next->datum;
        delete(&(tmp->right), next->datum);
        return;
    }
    if(!tmp->left)
        *root = tmp->right;
    else
        *root = tmp->left;
    free(tmp);
}

Node *leftMost(Node *root) {
    if(!root->left)
        return root;
    return leftMost(root->left);
}

void rebalance(Node **tree) {
    if(!(*tree)->left && !((*tree)->right))
        return;
    if((*tree)->bal > 1) {
        if((*tree)->left->bal == 1) {
            puts("ll");
            rotateRight(tree);
        } else {
            puts("lr");
            rotateLeft(&((*tree)->left));
            rotateRight(tree);
        }
    } else if((*tree)->bal < -1) {
        if((*tree)->right->bal == 1) {
            puts("rl");
            rotateRight(&((*tree)->right));
            rotateLeft(tree);
        } else {
            puts("rr");
            rotateLeft(tree);
        }
    }
}

void clear(Node **root) {
    Node *tmp = *root;
    if(!tmp) return;
    clear(&(tmp->left));
    clear(&(tmp->right));
    free(tmp);
    *root = NULL;
}

void print(Node *root, enum Color color) {
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

void writeTree(char *filename, Node *root) {
    FILE *fptr = fopen(filename, "w");
	if(!root) {
		fputs("clear", fptr);
		fclose(fptr);
		return;
	}
    writeNode(fptr, root);
    fclose(fptr);
}

void writeNode(FILE *fptr, Node *node) {
    if(!node)
        return;
    if(node->pos[0] == '\0')
        fprintf(fptr, "root %d\n", node->datum);
    else
        fprintf(fptr, "%s %d\n", node->pos, node->datum);
    writeNode(fptr, node->left);
    writeNode(fptr, node->right);
}

void randomize(enum Color color, Node **root, Vector *vector) {
    int path = rand() % 2;
    if(vector->size == 0)
        path = 1;
    int value;
    if(path && vector->size < 31) {
        value = rand() % MAX_BRIGHTNESS;
        insert(root, value);
        setPos(*root, "\0");
        appendVector(vector, value);
    } else if(vector->size != 0) {
        value = vector->data[rand() % vector->size];
        delete(root, value);
        setPos(*root, "\0");
        appendVector(vector, value);
        deleteVector(vector, value);
    }
    switch(color) {
        case RED:
            writeTree("./r.txt", *root);
            break;
        case GREEN:
            writeTree("./g.txt", *root);
            break;
        default:
            writeTree("./b.txt", *root);
            break;
    }
}

void initVector(Vector *vector) {
    vector->size = 0;
    vector->capacity = 31;
    vector->data = calloc(31, sizeof(int) * 31);
}

void appendVector(Vector *vector, int datum) {
    vector->data[vector->size++] = datum;
}

void deleteVector(Vector *vector, int datum) {
    for(size_t x = 0; x < vector->size; x++) {
        if(vector->data[x] == datum) {
            vector->size--;
            for(size_t i = x; i < vector->size; i++)
                vector->data[i] = vector->data[i + 1];
            vector->data[vector->size] = 0;
            return;
        }
    }
}

void clearVector(Vector *vector) {
    free(vector->data);
}