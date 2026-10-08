
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100003

typedef struct KeyNode {
    char *key;
    struct KeyNode *prev, *next;
    struct KeyNode *hnext;
    struct Bucket *bucket;
} KeyNode;

typedef struct Bucket {
    int count;
    struct Bucket *prev, *next;
    KeyNode *keys;
} Bucket;

typedef struct {
    Bucket *head, *tail;
    KeyNode *map[HASH_SIZE];
} AllOne;

unsigned int hash(char *s) {
    unsigned int h = 0;
    while (*s)
        h = h * 31 + *s++;
    return h % HASH_SIZE;
}

KeyNode* findKey(AllOne* obj, char* key) {
    KeyNode* p = obj->map[hash(key)];
    while (p) {
        if (strcmp(p->key, key) == 0)
            return p;
        p = p->hnext;
    }
    return NULL;
}

Bucket* newBucket(int count) {
    Bucket* b = calloc(1, sizeof(Bucket));
    b->count = count;
    return b;
}

void addKey(Bucket* b, KeyNode* k) {
    k->prev = NULL;
    k->next = b->keys;

    if (b->keys)
        b->keys->prev = k;

    b->keys = k;
    k->bucket = b;
}

void removeKey(KeyNode* k) {
    Bucket* b = k->bucket;

    if (k->prev)
        k->prev->next = k->next;
    else
        b->keys = k->next;

    if (k->next)
        k->next->prev = k->prev;
}

void insertAfter(AllOne* obj, Bucket* pos, Bucket* b) {
    b->prev = pos;

    if (pos) {
        b->next = pos->next;
        pos->next = b;
    } else {
        b->next = obj->head;
        obj->head = b;
    }

    if (b->next)
        b->next->prev = b;
    else
        obj->tail = b;
}

void deleteBucket(AllOne* obj, Bucket* b) {
    if (b->prev)
        b->prev->next = b->next;
    else
        obj->head = b->next;

    if (b->next)
        b->next->prev = b->prev;
    else
        obj->tail = b->prev;

    free(b);
}

AllOne* allOneCreate() {
    return calloc(1, sizeof(AllOne));
}

void allOneInc(AllOne* obj, char* key) {
    KeyNode* k = findKey(obj, key);

    if (!k) {
        k = calloc(1, sizeof(KeyNode));
        k->key = malloc(strlen(key) + 1);
        strcpy(k->key, key);

        unsigned int h = hash(key);
        k->hnext = obj->map[h];
        obj->map[h] = k;

        if (!obj->head || obj->head->count != 1) {
            Bucket* b = newBucket(1);
            insertAfter(obj, NULL, b);
        }

        addKey(obj->head, k);
        return;
    }

    Bucket* b = k->bucket;
    Bucket* next = b->next;

    if (!next || next->count != b->count + 1) {
        next = newBucket(b->count + 1);
        insertAfter(obj, b, next);
    }

    removeKey(k);
    addKey(next, k);

    if (!b->keys)
        deleteBucket(obj, b);
}

void allOneDec(AllOne* obj, char* key) {
    KeyNode* k = findKey(obj, key);

    if (!k)
        return;

    Bucket* b = k->bucket;

    if (b->count == 1) {
        removeKey(k);

        unsigned int h = hash(key);
        KeyNode** p = &obj->map[h];

        while (*p != k)
            p = &(*p)->hnext;

        *p = k->hnext;

        free(k->key);
        free(k);
    } else {
        Bucket* prev = b->prev;

        if (!prev || prev->count != b->count - 1) {
            prev = newBucket(b->count - 1);
            insertAfter(obj, b->prev, prev);
        }

        removeKey(k);
        addKey(prev, k);
    }

    if (!b->keys)
        deleteBucket(obj, b);
}

char* allOneGetMaxKey(AllOne* obj) {
    if (!obj->tail)
        return "";

    return obj->tail->keys->key;
}

char* allOneGetMinKey(AllOne* obj) {
    if (!obj->head)
        return "";

    return obj->head->keys->key;
}

void allOneFree(AllOne* obj) {
    for (int i = 0; i < HASH_SIZE; i++) {
        KeyNode* k = obj->map[i];

        while (k) {
            KeyNode* next = k->hnext;
            free(k->key);
            free(k);
            k = next;
        }
    }

    Bucket* b = obj->head;

    while (b) {
        Bucket* next = b->next;
        free(b);
        b = next;
    }

    free(obj);
}
