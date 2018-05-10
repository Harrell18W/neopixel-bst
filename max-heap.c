#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 1

typedef struct heap {
    size_t capacity; //max number of elements
    size_t size; //actual number of elements
    unsigned int *data; //array of elements
} Heap;

void push(Heap *heap, unsigned int datum);
unsigned int pop(Heap *heap);
unsigned int peek(Heap *heap);
void sift(Heap *heap, size_t index);
Heap *merge(Heap *heap1, Heap *heap2);
Heap *initialize(unsigned int *array, size_t index);
Heap *create();
void destroy(Heap *heap);
void resizeIfFull(Heap *heap);
void print(Heap *heap);
void writeTree(char *filename, Heap *heap);
void writeNode(FILE *fptr, Heap *heap, size_t index, char *pos, unsigned int size);

int main(void) {
    Heap *r = create();
    Heap *g = create();
    Heap *b = create();
}

void destroy(Heap *heap) {
    free(heap->data);
    heap->data = calloc(heap->capacity, sizeof(unsigned int));
    heap->size = 0;
    heap->capacity = 0;
    free(heap->data);
    free(heap);
}

Heap *create() {
    Heap *heap = malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = CAPACITY;
    heap->data = calloc(CAPACITY, sizeof(unsigned int)); //calloc initializes allocated memory to 0
    return heap;
}

Heap *initialize(unsigned int *array, size_t size) {
    Heap *heap = malloc(sizeof(Heap));
    heap->size = size;
    heap->capacity = size * 2;
    heap->data = calloc(heap->capacity, sizeof(unsigned int));
    memcpy(heap->data, array, sizeof(unsigned int) * size);
    for(size_t i = size/2-1; (int)i >= 0; i--)
        sift(heap, i);
    return heap;
}

Heap *merge(Heap *heap1, Heap *heap2) {
    unsigned int tmp[heap1->size + heap2->size];
    memcpy(tmp, heap1->data, sizeof(unsigned int) * heap1->size);
    memcpy(tmp + heap1->size, heap2->data, sizeof(unsigned int) * heap2->size);
    return initialize(tmp, heap1->size + heap2->size);
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
        if(heap->data[max] < heap->data[i*2+1])
            max = i*2+1;
        if(i*2+2 < heap->size && heap->data[max] < heap->data[i*2+2])
            max = i*2+2;
        if(max == i)
            break;
        else {
            tmp = heap->data[i];
            heap->data[i] = heap->data[max];
            heap->data[max] = tmp;
        }
    }
}

void resizeIfFull(Heap *heap) {
    if(heap->size >= heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(unsigned int)); //realloc makes a new block of memory with the new size and moves the old memory to the new location
    }
}

void print(Heap *heap) {
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

void push(Heap *heap, unsigned int datum) {
    resizeIfFull(heap);
    if(heap->size == 31) {
        puts("Max heap size reached");
        return;
    }
    heap->data[heap->size++] = datum;
    for(size_t ci = heap->size - 1, pi = (ci - 1)/2;
        ci > 0 && heap->data[pi] < heap->data[ci];
        ci = pi, pi = (ci-1)/2) {
        unsigned int tmp = heap->data[ci];
        heap->data[ci] = heap->data[pi];
        heap->data[pi] = tmp;
    }
}

void writeTree(char *filename, Heap *heap) {
    FILE *fptr = fopen(filename, "w");
    if(heap->size == 0) {
        fputs("clear", fptr);
        fclose(fptr);
        return;
    }
    fprintf(fptr, "root %d\n", heap->data[0]);
    char *pos = malloc(sizeof(char) * 2);
    if(heap->size >= 1)
        strcpy(pos, "l\0");
        writeNode(fptr, heap, 1, pos, 2);
    if(heap->size >= 2)
        strcpy(pos, "r\0");
        writeNode(fptr, heap, 2, pos, 2);
    free(pos);
    fclose(fptr);
}

void writeNode(FILE *fptr, Heap *heap, size_t index, char *pos, unsigned int size) {
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
        writeNode(fptr, heap, l_index, l_pos, size+1);
        free(l_pos);
    }
    if(r_index < heap->size) {
        char *r_pos = malloc(sizeof(char) * (size + 1));
        for(i = 0; pos[i] != '\0'; i++)
            r_pos[i] = pos[i];
        r_pos[i] = 'r';
        r_pos[i + 1] = '\0';
        writeNode(fptr, heap, r_index, r_pos, size+1);
        free(r_pos);
    }
}