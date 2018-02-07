#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPTH 4
#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255

typedef struct node {
    int datum;
    int height;
    int bal;
    char pos[MAX_DEPTH + 1];
    struct node *parent;
    struct node *left;
    struct node *right;
} Node;

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
void editTree(Node **root, enum Color color);

int main(void) {
    Node *r = NULL;
    Node *g = NULL;
    Node *b = NULL;
    int command = -1;
    while(1) {
        puts("Select a tree\nr:0\ng:1\nb:2");
        scanf("%d", &command);
        switch(command) {
            case 0:
                editTree(&r, RED);
                break;
            case 1:
                editTree(&g, GREEN);
                break;
            case 2:
                editTree(&b, BLUE);
                break;
            default:
                puts("Invalid command");
                break;
        }
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

void editTree(Node **root, enum Color color) {
    int command = -1;
    puts("\nWhat would you like to do?\nInsert node: 0\nDelete node: 1\nPrint tree:  2\nClear tree:  3");
    scanf("%d", &command);
    int brightness;
    char filename[6];
    if(color == RED)
        strcpy(filename, "r.txt");
    else if(color == GREEN)
        strcpy(filename, "g.txt");
    else
        strcpy(filename, "b.txt");
    switch(command) {
        case 0:
            printf("\nPlease insert a number between %d and %d\n", 0, 255);
            scanf("%d", &brightness);
            if(brightness < 0 || brightness > 255)
                puts("Please input a valid brightness\n");
            else {
                insert(root, brightness);
                setPos(*root, "\0");
                writeTree(filename, *root);
                puts("");
            }
            break;
        case 1:
            puts("\nPlease input your datum to remove");
            scanf("%d", &brightness);
            delete(root, brightness);
            setPos(*root, "\0");
            writeTree(filename, *root);
            puts("");
            break;
        case 2:
            print(*root, color);
            puts("");
            break;
        case 3:
            clear(root);
            writeTree(filename, *root);
            puts("");
            break;
        default:
            puts("Invalid command\n");
            break;
    }
}