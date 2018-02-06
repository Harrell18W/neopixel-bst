#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPTH 4
#define MIN_BRIGTHNESS 0
#define MAX_BRIGTHNESS 100

typedef struct node {
    int datum;
    char pos[MAX_DEPTH + 1];
    struct node *left;
    struct node *right;
} Node;

enum Color {RED = 31, GREEN = 32, BLUE = 34};

void insert(Node **root, int datum);
void delete(Node **root, int datum);
Node *leftMost(Node *root);
void setPos(Node *root, char *step);
void clear(Node **root);
void print(Node *root, enum Color color);
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

void insert(Node **root, int datum) {
    static int depth = 0;
    Node *tree = *root;
    if(depth > MAX_DEPTH) {
        printf("%d could not be inserted because doing so would make the tree greater than the maximum possible depth\n\n", datum);
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

void writeTree(char *filename, Node *root) {
    FILE *fptr = fopen(filename, "w");
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
            printf("\nPlease insert a number between %d and %d\n", MIN_BRIGTHNESS, MAX_BRIGTHNESS);
            scanf("%d", &brightness);
            if(brightness < MIN_BRIGTHNESS || brightness > MAX_BRIGTHNESS)
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