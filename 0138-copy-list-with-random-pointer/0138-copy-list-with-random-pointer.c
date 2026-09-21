#include <stdlib.h>

struct Node* copyRandomList(struct Node* head) {

    if (head == NULL)
        return NULL;

    struct Node* original[1000];
    struct Node* copy[1000];

    int n = 0;

    struct Node* current = head;

    while (current != NULL) {
        original[n] = current;

        copy[n] = malloc(sizeof(struct Node));
        copy[n]->val = current->val;

        current = current->next;
        n++;
    }

    for (int i = 0; i < n; i++) {

        if (i + 1 < n)
            copy[i]->next = copy[i + 1];
        else
            copy[i]->next = NULL;

        if (original[i]->random == NULL) {
            copy[i]->random = NULL;
        } else {

            for (int j = 0; j < n; j++) {
                if (original[i]->random == original[j]) {
                    copy[i]->random = copy[j];
                    break;
                }
            }
        }
    }

    return copy[0];
}