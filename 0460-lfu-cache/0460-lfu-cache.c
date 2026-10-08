
#include <stdlib.h>

#define HASH_SIZE 100003

typedef struct Node {
    int key, value, freq;
    struct Node *prev, *next;
    struct Node *hnext;
} Node;

typedef struct {
    Node *head, *tail;
} List;

typedef struct {
    int capacity, size, minFreq;
    Node *map[HASH_SIZE];
    List *freqList;
} LFUCache;

int hash(int key) {
    return (unsigned int)key % HASH_SIZE;
}

Node* findNode(LFUCache* obj, int key) {
    int h = hash(key);
    Node* curr = obj->map[h];

    while (curr) {
        if (curr->key == key)
            return curr;
        curr = curr->hnext;
    }
    return NULL;
}

void removeNode(List* list, Node* node) {
    if (node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;

    node->prev = node->next = NULL;
}

void addNode(List* list, Node* node) {
    node->prev = NULL;
    node->next = list->head;

    if (list->head)
        list->head->prev = node;
    else
        list->tail = node;

    list->head = node;
}

void updateFreq(LFUCache* obj, Node* node) {
    int freq = node->freq;

    removeNode(&obj->freqList[freq], node);

    if (freq == obj->minFreq &&
        obj->freqList[freq].head == NULL)
        obj->minFreq++;

    node->freq++;
    addNode(&obj->freqList[node->freq], node);
}

LFUCache* lFUCacheCreate(int capacity) {
    LFUCache* obj = calloc(1, sizeof(LFUCache));

    obj->capacity = capacity;
    obj->freqList = calloc(200001, sizeof(List));

    return obj;
}

int lFUCacheGet(LFUCache* obj, int key) {
    Node* node = findNode(obj, key);

    if (!node)
        return -1;

    updateFreq(obj, node);
    return node->value;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    if (obj->capacity == 0)
        return;

    Node* node = findNode(obj, key);

    if (node) {
        node->value = value;
        updateFreq(obj, node);
        return;
    }

    if (obj->size == obj->capacity) {
        Node* victim = obj->freqList[obj->minFreq].tail;

        removeNode(&obj->freqList[obj->minFreq], victim);

        int h = hash(victim->key);
        Node** p = &obj->map[h];

        while (*p != victim)
            p = &(*p)->hnext;

        *p = victim->hnext;
        free(victim);
        obj->size--;
    }

    Node* newNode = calloc(1, sizeof(Node));

    newNode->key = key;
    newNode->value = value;
    newNode->freq = 1;

    int h = hash(key);
    newNode->hnext = obj->map[h];
    obj->map[h] = newNode;

    addNode(&obj->freqList[1], newNode);

    obj->minFreq = 1;
    obj->size++;
}

void lFUCacheFree(LFUCache* obj) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = obj->map[i];

        while (curr) {
            Node* next = curr->hnext;
            free(curr);
            curr = next;
        }
    }

    free(obj->freqList);
    free(obj);
}
