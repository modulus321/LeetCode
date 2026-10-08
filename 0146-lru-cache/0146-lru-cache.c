
#include <stdlib.h>

#define SIZE 100003

typedef struct Node {
    int key, value;
    struct Node *prev, *next;
    struct Node *hnext;
} Node;

typedef struct {
    int capacity, size;
    Node *head, *tail;
    Node *map[SIZE];
} LRUCache;

int hash(int key) {
    return (unsigned int)key % SIZE;
}

Node* findNode(LRUCache* obj, int key) {
    Node* p = obj->map[hash(key)];

    while (p) {
        if (p->key == key)
            return p;
        p = p->hnext;
    }

    return NULL;
}

void removeNode(LRUCache* obj, Node* node) {
    if (node->prev)
        node->prev->next = node->next;
    else
        obj->head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        obj->tail = node->prev;
}

void addFront(LRUCache* obj, Node* node) {
    node->prev = NULL;
    node->next = obj->head;

    if (obj->head)
        obj->head->prev = node;
    else
        obj->tail = node;

    obj->head = node;
}

void moveFront(LRUCache* obj, Node* node) {
    if (obj->head == node)
        return;

    removeNode(obj, node);
    addFront(obj, node);
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = calloc(1, sizeof(LRUCache));
    obj->capacity = capacity;
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node* node = findNode(obj, key);

    if (!node)
        return -1;

    moveFront(obj, node);
    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (obj->capacity == 0)
        return;

    Node* node = findNode(obj, key);

    if (node) {
        node->value = value;
        moveFront(obj, node);
        return;
    }

    if (obj->size == obj->capacity) {
        Node* last = obj->tail;

        removeNode(obj, last);

        int h = hash(last->key);
        Node** p = &obj->map[h];

        while (*p != last)
            p = &(*p)->hnext;

        *p = last->hnext;

        free(last);
        obj->size--;
    }

    Node* newNode = malloc(sizeof(Node));

    newNode->key = key;
    newNode->value = value;

    int h = hash(key);
    newNode->hnext = obj->map[h];
    obj->map[h] = newNode;

    addFront(obj, newNode);
    obj->size++;
}

void lRUCacheFree(LRUCache* obj) {
    Node* curr = obj->head;

    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }

    free(obj);
}
