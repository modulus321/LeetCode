
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *left;
    char *right;
    int l, r;
    int capacity;
} TextEditor;

TextEditor* textEditorCreate() {
    TextEditor* obj = malloc(sizeof(TextEditor));

    obj->capacity = 1000000;
    obj->left = malloc(obj->capacity);
    obj->right = malloc(obj->capacity);

    obj->l = 0;
    obj->r = 0;

    return obj;
}

void textEditorAddText(TextEditor* obj, char* text) {
    while (*text) {
        obj->left[obj->l++] = *text++;
    }
}

int textEditorDeleteText(TextEditor* obj, int k) {
    int deleted = k < obj->l ? k : obj->l;
    obj->l -= deleted;
    return deleted;
}

char* getLast10(TextEditor* obj) {
    int start = obj->l > 10 ? obj->l - 10 : 0;
    int len = obj->l - start;

    char* result = malloc(len + 1);

    memcpy(result, obj->left + start, len);
    result[len] = '\0';

    return result;
}

char* textEditorCursorLeft(TextEditor* obj, int k) {
    while (k-- > 0 && obj->l > 0) {
        obj->right[obj->r++] = obj->left[--obj->l];
    }

    return getLast10(obj);
}

char* textEditorCursorRight(TextEditor* obj, int k) {
    while (k-- > 0 && obj->r > 0) {
        obj->left[obj->l++] = obj->right[--obj->r];
    }

    return getLast10(obj);
}

void textEditorFree(TextEditor* obj) {
    free(obj->left);
    free(obj->right);
    free(obj);
}
