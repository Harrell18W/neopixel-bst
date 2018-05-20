#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//avl and bst parameters
#define MAX_DEPTH 4

//heap parameters
#define CAPACITY 31

//data structure types
enum Type {AVL, BST, HEAP};

//operations
enum Operation {INSERT, DELETE, CLEAR, SWITCH};

//heap types
enum HeapType {MIN, MAX};

typedef struct bstNode {
    int datum;
    char pos[MAX_DEPTH + 1];
    struct bstNode *left;
    struct bstNode *right;
} BstNode;

typedef struct avlNode {
    int datum;
    int height;
    int bal;
    char pos[MAX_DEPTH + 1];
    struct avlNode *parent;
    struct avlNode *left;
    struct avlNode *right;
} AvlNode;

typedef struct heap {
    unsigned int type;
    size_t capacity;
    size_t size;
    unsigned int *data;
} Heap;

enum Color {RED = 31, GREEN = 32, BLUE = 34};

//bst functions
void bstInsert(BstNode **root, int datum);
void bstDelete(BstNode **root, int datum);
BstNode *bstLeftMost(BstNode *root);
void bstSetPos(BstNode *root, char *step);
void bstClear(BstNode **root);
void bstPrint(BstNode *root, enum Color color);
void bstWriteTree(char *filename, BstNode *root);
void bstWriteNode(FILE *fptr, BstNode *node);

//avl functions
int maxHeight(AvlNode *node);
int balance(AvlNode *node);
void balanceTree(AvlNode *node);
void balanceTreeS2(AvlNode *root);
void rotateLeft(AvlNode **node);
void rotateRight(AvlNode **node);
void avlInsert(AvlNode **tree, int datum);
void avlInsertBST(AvlNode **tree, AvlNode *node);
void avlDelete(AvlNode **root, int datum);
AvlNode *avlLeftMost(AvlNode *root);
void rebalance(AvlNode **tree);
void avlClear(AvlNode **root);
void avlPrint(AvlNode *root, enum Color color);
void avlSetPos(AvlNode *root, char *step);
void avlWriteTree(char *filename, AvlNode *root);
void avlWriteNode(FILE *fptr, AvlNode *node);

//heap functions
void push(Heap *heap, unsigned int datum);
unsigned int pop(Heap *heap);
unsigned int peek(Heap *heap);
void sift(Heap *heap, size_t index);
Heap *create(unsigned int type);
void destroy(Heap **heapPtr);
void heapPrint(Heap *heap);
void heapWriteTree(char *filename, Heap *heap);
void heapWriteNode(FILE *fptr, Heap *heap, size_t index, char *pos, unsigned int size);

void handle(enum Color color, enum Operation operation, unsigned int datum, enum Type type, enum HeapType heapType);

int main(void) {

    return 0;
}

void handle(enum Color color, enum Operation operation, unsigned int datum, enum Type type, enum HeapType heapType) {
    //INSERT, DELETE, CLEAR, SWITCH
    static AvlNode *avlR = NULL;
    static AvlNode *avlG = NULL;
    static AvlNode *avlB = NULL;

    static BstNode *bstR = NULL;
    static BstNode *bstG = NULL;
    static BstNode *bstB = NULL;

    static Heap *heapR = NULL;
    static Heap *heapG = NULL;
    static Heap *heapB = NULL;

    static int currType = -1;
    
    int tmp;
    
    switch(operation) {
        case INSERT:
            switch(currType) {
                case AVL:
                    switch(color) {
                        case RED:
                            avlInsert(&avlR, datum);
                            avlSetPos(avlR, "\0");
                            avlWriteTree("r.txt", avlR);
                            break;
                        
                        case GREEN:
                            avlInsert(&avlG, datum);
                            avlSetPos(avlG, "\0");
                            avlWriteTree("g.txt", avlG);
                            break;

                        case BLUE:
                            avlInsert(&avlB, datum);
                            avlSetPos(avlB, "\0");
                            avlWriteTree("b.txt", avlB);
                            break;
                        
                        default:
                            puts("Invalid color used in call to handle");
                    }
                    break;

                case BST:
                    switch(color) {
                        case RED:
                            bstInsert(&bstR, datum);
                            bstSetPos(bstR, "\0");
                            bstWriteTree("r.txt", bstR);
                            break;
                        
                        case GREEN:
                            bstInsert(&bstG, datum);
                            bstSetPos(bstG, "\0");
                            bstWriteTree("g.txt", bstG);
                            break;

                        case BLUE:
                            bstInsert(&bstB, datum);
                            bstSetPos(bstB, "\0");
                            bstWriteTree("b.txt", bstB);
                            break;
                        
                        default:
                            puts("Invalid color used in call to handle");
                    }
                    break;
                
                case HEAP:
                    switch(color) {
                        case RED:
                            push(heapR, datum);
                            heapWriteTree("r.txt", heapR);
                            break;
                        
                        case GREEN:
                            push(heapG, datum);
                            heapWriteTree("g.txt", heapG);
                            break;

                        case BLUE:
                            push(heapB, datum);
                            heapWriteTree("b.txt", heapB);
                            break;
                        
                        default:
                            puts("Invalid color used in call to handle");
                    }
                    break;

                    default:
                        puts("Invalid value stored in currType");
            }
            break;
        
        case DELETE:
            switch(currType) {
                case AVL:
                    switch(color) {
                        case RED:
                            avlDelete(&avlR, datum);
                            avlSetPos(avlR, "\0");
                            avlWriteTree("r.txt", avlR);
                            break;

                        case GREEN:
                            avlDelete(&avlG, datum);
                            avlSetPos(avlG, "\0");
                            avlWriteTree("g.txt", avlG);
                            break;

                        case BLUE:
                            avlDelete(&avlB, datum);
                            avlSetPos(avlB, "\0");
                            avlWriteTree("b.txt", avlB);
                            break;
                        
                        default:
                            puts("Invalid color used in call to handle");
                    }
                    break;
                
                case BST:
                    switch(color) {
                        case RED:
                            bstDelete(&bstR, datum);
                            bstSetPos(bstR, "\0");
                            bstWriteTree("r.txt", bstR);
                            break;

                        case GREEN:
                            bstDelete(&bstG, datum);
                            bstSetPos(bstG, "\0");
                            bstWriteTree("g.txt", bstG);
                            break;

                        case BLUE:
                            bstDelete(&bstB, datum);
                            bstSetPos(bstB, "\0");
                            bstWriteTree("b.txt", bstB);
                            break;

                        default:
                            puts("Invalid color used in call to handle");
                    }
                    break;

                case HEAP:
                    switch(color) {
                        case RED:
                            pop(heapR);
                            heapWriteTree("r.txt", heapR);
                            break;

                        case GREEN:
                            pop(heapG);
                            heapWriteTree("g.txt", heapG);
                            break;

                        case BLUE:
                            pop(heapB);
                            heapWriteTree("b.txt", heapB);
                            break;

                        default:
                            puts("Invalid color used in call to handle");
                    }
                    break;

                default:
                    puts("Invalid value stored in curr type");
            }
            break;
        
        case CLEAR:
            switch(currType) {
                case AVL:
                    switch(color) {
                        case RED:
                            avlClear(&avlR);
                            avlWriteTree("r.txt", avlR);
                            break;

                        case GREEN:
                            avlClear(&avlG);
                            avlWriteTree("g.txt", avlG);
                            break;

                        case BLUE:
                            avlClear(&avlB);
                            avlWriteTree("b.txt", avlB);
                            break;

                        default:
                            puts("Invalid color used in call to handle");
                    }
                    break;

                case BST:
                    switch(color) {
                        case RED:
                            bstClear(&bstR);
                            bstWriteTree("r.txt", bstR);
                            break;

                        case GREEN:
                            bstClear(&bstG);
                            bstWriteTree("g.txt", bstG);
                            break;

                        case BLUE:
                            bstClear(&bstB);
                            bstWriteTree("b.txt", bstB);
                            break;

                        default:
                            puts("Invalid color used in call to handle");
                    }
                    break;

                case HEAP:
                    switch(color) {
                        case RED:
                            tmp = heapR->type;
                            destroy(&heapR);
                            heapR = create(tmp);
                            heapWriteTree("r.txt", heapR);
                            break;

                        case GREEN:
                            tmp = heapG->type;
                            destroy(&heapG);
                            heapG = create(tmp);
                            heapWriteTree("g.txt", heapG);
                            break;

                        case BLUE:
                            tmp = heapB->type;
                            destroy(&heapB);
                            heapB = create(tmp);
                            heapWriteTree("b.txt", heapB);
                            break;

                        default:
                            puts("Invalid color used in call to handle");
                    }
                    break;

                default:
                    puts("Invalid value stored in currType");
            }
            break;

        case SWITCH:
            switch(currType) {
                case AVL:
                    if(type != AVL) {
                        avlClear(&avlR);
                        avlClear(&avlG);
                        avlClear(&avlB);
                        switch(type) {
                            case BST:
                                currType = BST;
                                break;
                            
                            case HEAP:
                                heapR = create(heapType);
                                heapG = create(heapType);
                                heapB = create(heapType);
                                currType = HEAP;
                                break;

                            default:
                                puts("Invalid type used in call to handle");
                        }
                        break;
                    } else {
                        puts("handle is already using AVL");
                        return;
                    }
                    break;

                case BST:
                    if(currType != BST) {
                        bstClear(&bstR);
                        bstClear(&bstG);
                        bstClear(&bstB);
                        bstWriteTree("r.txt", bstR);
                        bstWriteTree("g.txt", bstR);
                        bstWriteTree("b.txt", bstR);
                        switch(type) {
                            case AVL:
                                currType = AVL;
                                break;
                            
                            case HEAP:
                                heapR = create(heapType);
                                heapG = create(heapType);
                                heapB = create(heapType);
                                currType = HEAP;
                                break;

                            default:
                                puts("Invalid type used in call to handle");
                        }
                        break;
                    } else {
                        puts("handle is already using BST");
                        return;
                    }
                    break;

                case HEAP:
                    if(currType != HEAP) {
                        destroy(&heapR);
                        destroy(&heapG);
                        destroy(&heapB);
                        heapWriteTree("r.txt", heapR);
                        heapWriteTree("g.txt", heapR);
                        heapWriteTree("b.txt", heapR);
                        switch(type) {
                            case AVL:
                                currType = AVL;
                                break;

                            case BST:
                                currType = BST;
                                break;

                            default:
                                puts("Invalid type used in call to handle");
                        }
                        break;
                    } else {
                        puts("handle is already using HEAP");
                        return;
                    }
                    break;

                default:
                    puts("Invalid value stored in currType");
            }
            break;

        default:
            puts("Invalid command passed to handle");
    }
}

//bst functions

void bstInsert(BstNode **root, int datum) {
    static int depth = 0;
    BstNode *tree = *root;
    if(depth > MAX_DEPTH) {
        printf("%d could not be inserted because doing so would make the tree greater than the maximum possible depth\n\n", datum);
        return;
    }
    if(!tree) {
        *root = malloc(sizeof(BstNode));
        tree = *root;
        tree->pos[0] = '\0';
        tree->left = NULL;
        tree->right = NULL;
        tree->datum = datum;
        return;
    }
    if(tree->datum > datum) {
        depth++;
        bstInsert(&(tree->left), datum);
        depth--;
        return;
    } else {
        depth++;
        bstInsert(&(tree->right), datum);
        depth--;
    }
}

void bstDelete(BstNode **root, int datum) {
    BstNode *tree = *root;
    if(!tree) {
        printf("%d not found in tree\n", datum);
        return;
    }
    if(datum < tree->datum) {
        bstDelete(&(tree->left), datum);
        return;
    }
    if(datum > tree->datum) {
        bstDelete(&(tree->right), datum);
        return;
    }
    if(tree->left && tree->right) {
        BstNode *newNode = bstLeftMost(tree->right);
        tree->datum = newNode->datum;
        bstDelete(&(tree->right), newNode->datum);
        return;
    }
    if(!tree->left)
        *root = tree->right;
    else
        *root = tree->left;
    free(tree);
}

BstNode *bstLeftMost(BstNode *root) {
    if(!root->left)
        return root;
    return bstLeftMost(root->left);
}

void bstSetPos(BstNode *root, char *step) {
    if(!root)
        return;
    size_t x;
    strcpy(root->pos, step);
    char l[5], r[5];
    for(x = 0; step[x] != '\0'; x++)
        l[x] = step[x];
    l[x] = 'l';
    l[x+1] = '\0';
    for(x = 0; step[x] != '\0'; x++)
        r[x] = step[x];
    r[x] = 'r';
    r[x+1] = '\0';
    bstSetPos(root->left, l);
    bstSetPos(root->right, r);
}

void bstClear(BstNode **root) {
    BstNode *node = *root;
    if(!node)
        return;
    bstClear(&(node->left));
    bstClear(&(node->right));
    free(node);
    *root = NULL;
}

void bstPrint(BstNode *root, enum Color color) {
    static int depth = 0;
    if(!root)
        return;
    depth++;
    bstPrint(root->right, color);
    depth--;
    for(int x = 0; x < depth; x++)
        printf("  ");
    printf("\x1b[%dm%d:%s\x1b[0m\n", color, root->datum, root->pos);
    depth++;
    bstPrint(root->left, color);
    depth--;
}

void bstWriteTree(char *filename, BstNode *root) {
    FILE *fptr = fopen(filename, "w");
    if(!root) {
        fputs("clear", fptr);
        fclose(fptr);
        return;
    }
    bstWriteNode(fptr, root);
    fclose(fptr);
}

void bstWriteNode(FILE *fptr, BstNode *node) {
    if(!node)
        return;
    if(node->pos[0] == '\0')
        fprintf(fptr, "root %d\n", node->datum);
    else
        fprintf(fptr, "%s %d\n", node->pos, node->datum);
    bstWriteNode(fptr, node->left);
    bstWriteNode(fptr, node->right);
}

//avl functions

int maxHeight(AvlNode *node) {
    int l = -1, r = -1;
    if(node->left)
        l = node->left->height;
    if(node->right)
        r = node->right->height;
    return l > r? l : r;
}

int balance(AvlNode *node) {
    int l = -1, r = -1;
    if(node->left)
        l = node->left->height;
    if(node->right)
        r = node->right->height;
    printf("bal: %d\n", l - r);
    return l - r;
}

void balanceTree(AvlNode *node) {
    AvlNode *curr = node->parent? node->parent : node;
    while(curr->parent)
        curr = curr->parent;
    balanceTreeS2(curr);
}

void balanceTreeS2(AvlNode *root) {
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

void rotateLeft(AvlNode **node) {
    AvlNode *oldRoot = *node;
    AvlNode *newRoot = oldRoot->right;
    oldRoot->right = newRoot->left? newRoot->left: NULL;
    if(oldRoot->right)
        oldRoot->right->parent = oldRoot;
    newRoot->left = oldRoot;
    oldRoot->height = 1 + maxHeight(oldRoot);
    newRoot->height = 1 + maxHeight(oldRoot);

    if(oldRoot->parent) {
        AvlNode *g = oldRoot->parent;
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

void rotateRight(AvlNode **node) {
    AvlNode *oldRoot = *node;
    AvlNode *newRoot = oldRoot->left;
    oldRoot->left = newRoot->right? newRoot->right: NULL;
    if(oldRoot->left)
        oldRoot->left->parent = oldRoot;
    newRoot->right = oldRoot;
    oldRoot->height = 1 + maxHeight(oldRoot);
    newRoot->height = 1 + maxHeight(oldRoot);

    if(oldRoot->parent) {
        AvlNode *g = oldRoot->parent;
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

void avlInsert(AvlNode **tree, int datum) {
    AvlNode *newNode = malloc(sizeof(AvlNode));
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->datum = datum;
    newNode->height = 0;
    avlInsertBST(tree, newNode);
    while(newNode->parent)
        newNode = newNode->parent;
    *tree = newNode;
}

void avlInsertBST(AvlNode **tree, AvlNode *node) {
    static int depth = 0;
    if(depth > MAX_DEPTH) {
        printf("%d could not be inserted because doing so would make the tree greater than the maximum possible depth\n\n", node->datum);
        return;
    }
    if(*tree && node->datum < (*tree)->datum) {
        if((*tree)->left) {
            depth++;
            avlInsertBST(&(*tree)->left, node);
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
            avlInsertBST(&(*tree)->right, node);
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

void avlDelete(AvlNode **root, int datum) {
    AvlNode *tmp = *root;
    if(!tmp) {
        printf("%d not found in tree\n", datum);
        return;
    }
    if(datum < tmp->datum) {
        avlDelete(&(tmp->left), datum);
        (*root)->height = 1 + maxHeight(*root);
        balanceTree(*root);
        rebalance(root);
        return;
    }
    if(datum > tmp->datum) {
        avlDelete(&(tmp->right), datum);
        (*root)->height = 1 + maxHeight(*root);
        balanceTree(*root);
        rebalance(root);
        return;
    }
    if(tmp->left && tmp->right) {
        AvlNode *next = avlLeftMost(tmp->right);
        tmp->datum = next->datum;
        avlDelete(&(tmp->right), next->datum);
        return;
    }
    if(tmp->left && tmp->right) {
        AvlNode *next = avlLeftMost(tmp->right);
        tmp->datum = next->datum;
        avlDelete(&(tmp->right), next->datum);
        return;
    }
    if(!tmp->left)
        *root = tmp->right;
    else
        *root = tmp->left;
    free(tmp);
}

AvlNode *avlLeftMost(AvlNode *root) {
    if(!root->left)
        return root;
    return avlLeftMost(root->left);
}

void rebalance(AvlNode **tree) {
    if(!(*tree)->left && !((*tree)->right))
        return;
    if((*tree)->bal > 1) {
        if((*tree)->left->bal == 1) {
            rotateRight(tree);
        } else {
            rotateLeft(&((*tree)->left));
            rotateRight(tree);
        }
    } else if((*tree)->bal < -1) {
        if((*tree)->right->bal == 1) {
            rotateRight(&((*tree)->right));
            rotateLeft(tree);
        } else {
            rotateLeft(tree);
        }
    }
}

void avlClear(AvlNode **root) {
    AvlNode *tmp = *root;
    if(!tmp) return;
    avlClear(&(tmp->left));
    avlClear(&(tmp->right));
    free(tmp);
    *root = NULL;
}

void avlPrint(AvlNode *root, enum Color color) {
    //red: 31   green: 32   blue: 34
    static int depth = 0;
    if(!root)
        return;
    depth++;
    avlPrint(root->right, color);
    depth--;
    for(int x = 0; x < depth; x++)
        printf("  ");
    printf("\x1b[%dm%d:%s\x1b[0m\n", color, root->datum, root->pos);
    depth++;
    avlPrint(root->left, color);
    depth--;
}

void avlSetPos(AvlNode *root, char *step) {
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
    avlSetPos(root->left, l);
    avlSetPos(root->right, r);
}

void avlWriteTree(char *filename, AvlNode *root) {
    FILE *fptr = fopen(filename, "w");
	if(!root) {
		fputs("clear", fptr);
		fclose(fptr);
		return;
	}
    avlWriteNode(fptr, root);
    fclose(fptr);
}

void avlWriteNode(FILE *fptr, AvlNode *node) {
    if(!node)
        return;
    if(node->pos[0] == '\0')
        fprintf(fptr, "root %d\n", node->datum);
    else
        fprintf(fptr, "%s %d\n", node->pos, node->datum);
    avlWriteNode(fptr, node->left);
    avlWriteNode(fptr, node->right);
}

//heap functions

void push(Heap *heap, unsigned int datum) {
    if(heap->size == CAPACITY) {
        puts("Max heap size reached");
        return;
    }
    heap->data[heap->size++] = datum;
    if(heap->type == MAX) {
        for(size_t ci = heap->size - 1, pi = (ci - 1)/2;
            ci > 0 && heap->data[pi] < heap->data[ci];
            ci = pi, pi = (ci-1)/2) {
            unsigned int tmp = heap->data[ci];
            heap->data[ci] = heap->data[pi];
            heap->data[pi] = tmp;
        }
    } else {
        for(size_t ci = heap->size - 1, pi = (ci - 1)/2;
            ci > 0 && heap->data[pi] > heap->data[ci];
            ci = pi, pi = (ci-1)/2) {
            unsigned int tmp = heap->data[ci];
            heap->data[ci] = heap->data[pi];
            heap->data[pi] = tmp;
        }
    }
}

unsigned int pop(Heap *heap) {
    unsigned int out = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    sift(heap, 0);
    return out;
}

unsigned int peek(Heap *heap) {
    return heap->data[0];
}

void sift(Heap *heap, size_t index) {
    size_t max = index;
    unsigned int tmp;
    for(size_t i = max; i*2+1 < heap->size; i = max) {
        //max = i;
        if(heap->type == MAX) {
            if(heap->data[max] < heap->data[i*2+1])
                max = i*2+1;
            if(i*2+2 < heap->size && heap->data[max] < heap->data[i*2+2])
                max = i*2+2;
        } else {
            if(heap->data[max] > heap->data[i*2+1])
                max = i*2+1;
            if(i*2+2 < heap->size && heap->data[max] > heap->data[i*2+2])
                max = i*2+2;
        }
        if(max == i)
            break;
        else {
            tmp = heap->data[i];
            heap->data[i] = heap->data[max];
            heap->data[max] = tmp;
        }
    }
}

Heap *create(unsigned int type) {
    Heap *heap = malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = CAPACITY;
    heap->type = type;
    heap->data = calloc(CAPACITY, sizeof(unsigned int));
    return heap;
}

void destroy(Heap **heapPtr) {
    Heap *heap = *heapPtr;
    free(heap->data);
    heap->data = calloc(heap->capacity, sizeof(unsigned int));
    heap->size = 0;
    heap->capacity = 0;
    heap->type = 0;
    free(heap->data);
    free(heap);
    *heapPtr = NULL;
}

void heapPrint(Heap *heap) {
    int curr = 0;
    int layerMax = 1;
    while(curr < (int)heap->size) {
        printf("%d ", heap->data[curr++]);
        if(curr >= layerMax) {
            layerMax *= 2;
            layerMax++;
            printf("\n");
            for(int x = 0; x < curr; x++)
                printf(" ");
        }
    }
    printf("\n");
}

void heapWriteTree(char *filename, Heap *heap) {
    FILE *fptr = fopen(filename, "w");
    if(!heap || heap->size == 0) {
        fputs("clear", fptr);
        fclose(fptr);
        return;
    }
    fprintf(fptr, "root %d\n", heap->data[0]);
    char *pos = malloc(sizeof(char) * 2);
    if(heap->size >= 1) {
        strcpy(pos, "l\0");
        heapWriteNode(fptr, heap, 1, pos, 2);
    }
    if(heap->size >= 2) {
        strcpy(pos, "r\0");
        heapWriteNode(fptr, heap, 2, pos, 2);
    }
    free(pos);
    fclose(fptr);
}

void heapWriteNode(FILE *fptr, Heap *heap, size_t index, char *pos, unsigned int size) {
    fprintf(fptr, "%s %d\n", pos, heap->data[index]);
    size_t l_index = index*2+1;
    size_t r_index = index*2+2;
    size_t i;
    if(l_index < heap->size) {
        char *l_pos = malloc(sizeof(char) * (size + 1));
        for(i = 0; pos[i] != '\0'; i++)
            l_pos[i] = pos[i];
        l_pos[i] = 'l';
        l_pos[i + 1] = '\0';
        heapWriteNode(fptr, heap, l_index, l_pos, size+1);
        free(l_pos);
    }
    if(r_index < heap->size) {
        char *r_pos = malloc(sizeof(char) * (size + 1));
        for(i = 0; pos[i] != '\0'; i++)
            r_pos[i] = pos[i];
        r_pos[i] = 'r';
        r_pos[i + 1] = '\0';
        heapWriteNode(fptr, heap, r_index, r_pos, size+1);
        free(r_pos);
    }
}