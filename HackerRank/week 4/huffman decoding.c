#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char data;
    int freq;
    struct node *left, *right;
};

struct MinHeap {
    int size;
    int capacity;
    struct node **array;
};

struct node* newNode(char data, int freq) {
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data = data;
    n->freq = freq;
    n->left = n->right = NULL;
    return n;
}

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (struct node**)malloc(capacity * sizeof(struct node*));
    return heap;
}

void swapNode(struct node** a, struct node** b) {
    struct node* t = *a; *a = *b; *b = t;
}

void minHeapify(struct MinHeap* heap, int idx) {
    int smallest = idx;
    int l = 2*idx + 1;
    int r = 2*idx + 2;
    if (l < heap->size && heap->array[l]->freq < heap->array[smallest]->freq) smallest = l;
    if (r < heap->size && heap->array[r]->freq < heap->array[smallest]->freq) smallest = r;
    if (smallest != idx) {
        swapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

struct node* extractMin(struct MinHeap* heap) {
    struct node* tmp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return tmp;
}

void insertMinHeap(struct MinHeap* heap, struct node* item) {
    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = item;
    while (i && heap->array[i]->freq < heap->array[(i-1)/2]->freq) {
        swapNode(&heap->array[i], &heap->array[(i-1)/2]);
        i = (i-1)/2;
    }
}

void buildMinHeap(struct MinHeap* heap) {
    int n = heap->size;
    for (int i = (n-1)/2; i >= 0; i--) minHeapify(heap, i);
}

struct MinHeap* createAndBuildMinHeap(int freq[256]) {
    struct MinHeap* heap = createMinHeap(256);
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            heap->array[heap->size++] = newNode((char)i, freq[i]);
        }
    }
    buildMinHeap(heap);
    return heap;
}

struct node* buildHuffmanTree(int freq[256]) {
    struct MinHeap* heap = createAndBuildMinHeap(freq);
    if (heap->size == 0) return NULL;
    while (heap->size > 1) {
        struct node* left = extractMin(heap);
        struct node* right = extractMin(heap);
        struct node* top = newNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(heap, top);
    }
    return extractMin(heap);
}

void storeCodes(struct node* root, char arr[], int top, char codes[256][256]) {
    if (!root) return;
    if (!root->left && !root->right) {
        if (top == 0) { // single unique character: give it code "0"
            arr[top++] = '0';
        }
        arr[top] = '\0';
        strcpy(codes[(unsigned char)root->data], arr);
        return;
    }
    if (root->left) {
        arr[top] = '0';
        storeCodes(root->left, arr, top+1, codes);
    }
    if (root->right) {
        arr[top] = '1';
        storeCodes(root->right, arr, top+1, codes);
    }
}

/* This is the function HackerRank asks you to implement.
   It prints the decoded string (follow zeros/ones until a leaf). */
void decode_huff(struct node *root, char *s) {
    struct node *curr = root;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '0') curr = curr->left;
        else curr = curr->right;
        if (!curr->left && !curr->right) {
            putchar(curr->data);
            curr = root;
        }
    }
    putchar('\n');
}

int main() {
    char input[10001];
    if (!fgets(input, sizeof(input), stdin)) return 0;
    size_t len = strlen(input);
    if (len && input[len-1] == '\n') input[len-1] = '\0';

    int freq[256] = {0};
    for (size_t i = 0; input[i]; ++i) freq[(unsigned char)input[i]]++;

    struct node* root = buildHuffmanTree(freq);
    if (!root) { printf("\n"); return 0; }

    char codes[256][256];
    for (int i = 0; i < 256; ++i) codes[i][0] = '\0';
    char arr[256];
    storeCodes(root, arr, 0, codes);

    // build encoded bitstring
    int total_len = 0;
    for (size_t i = 0; input[i]; ++i) total_len += strlen(codes[(unsigned char)input[i]]);
    char *encoded = (char*)malloc(total_len + 1);
    encoded[0] = '\0';
    for (size_t i = 0; input[i]; ++i) strcat(encoded, codes[(unsigned char)input[i]]);

    // Now decode using the Huffman tree (this should produce the original string)
    decode_huff(root, encoded);

    free(encoded);
    return 0;
}
