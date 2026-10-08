
#include <stdlib.h>

#define SIZE 100005

typedef struct {
    int left[SIZE], right[SIZE];
    int lh, lt, rh, rt;
    int ls, rs;
} FrontMiddleBackQueue;

FrontMiddleBackQueue* frontMiddleBackQueueCreate() {
    FrontMiddleBackQueue* obj = calloc(1, sizeof(FrontMiddleBackQueue));
    obj->lh = obj->lt = SIZE / 2;
    obj->rh = obj->rt = SIZE / 2;
    return obj;
}

void balance(FrontMiddleBackQueue* obj) {
    if (obj->ls > obj->rs + 1) {
        int val = obj->left[--obj->lt];
        obj->ls--;

        obj->rh = (obj->rh - 1 + SIZE) % SIZE;
        obj->right[obj->rh] = val;
        obj->rs++;
    }
    else if (obj->ls < obj->rs) {
        int val = obj->right[obj->rh];
        obj->rh = (obj->rh + 1) % SIZE;
        obj->rs--;

        obj->left[obj->lt] = val;
        obj->lt = (obj->lt + 1) % SIZE;
        obj->ls++;
    }
}

void frontMiddleBackQueuePushFront(FrontMiddleBackQueue* obj, int val) {
    obj->lh = (obj->lh - 1 + SIZE) % SIZE;
    obj->left[obj->lh] = val;
    obj->ls++;
    balance(obj);
}

void frontMiddleBackQueuePushMiddle(FrontMiddleBackQueue* obj, int val) {
    if (obj->ls > obj->rs) {
        int x = obj->left[(obj->lt - 1 + SIZE) % SIZE];
        obj->lt = (obj->lt - 1 + SIZE) % SIZE;
        obj->ls--;

        obj->rh = (obj->rh - 1 + SIZE) % SIZE;
        obj->right[obj->rh] = x;
        obj->rs++;
    }

    obj->left[obj->lt] = val;
    obj->lt = (obj->lt + 1) % SIZE;
    obj->ls++;
}

void frontMiddleBackQueuePushBack(FrontMiddleBackQueue* obj, int val) {
    obj->right[obj->rt] = val;
    obj->rt = (obj->rt + 1) % SIZE;
    obj->rs++;
    balance(obj);
}

int frontMiddleBackQueuePopFront(FrontMiddleBackQueue* obj) {
    if (obj->ls + obj->rs == 0)
        return -1;

    int val = obj->left[obj->lh];
    obj->lh = (obj->lh + 1) % SIZE;
    obj->ls--;

    balance(obj);
    return val;
}

int frontMiddleBackQueuePopMiddle(FrontMiddleBackQueue* obj) {
    if (obj->ls + obj->rs == 0)
        return -1;

    obj->lt = (obj->lt - 1 + SIZE) % SIZE;
    int val = obj->left[obj->lt];
    obj->ls--;

    balance(obj);
    return val;
}

int frontMiddleBackQueuePopBack(FrontMiddleBackQueue* obj) {
    if (obj->ls + obj->rs == 0)
        return -1;

    int val;

    if (obj->rs > 0) {
        obj->rt = (obj->rt - 1 + SIZE) % SIZE;
        val = obj->right[obj->rt];
        obj->rs--;
    } else {
        obj->lt = (obj->lt - 1 + SIZE) % SIZE;
        val = obj->left[obj->lt];
        obj->ls--;
    }

    balance(obj);
    return val;
}

void frontMiddleBackQueueFree(FrontMiddleBackQueue* obj) {
    free(obj);
}
