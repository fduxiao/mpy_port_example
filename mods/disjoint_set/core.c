#include <stdlib.h>
#include "core.h"

disjoint_set_t disjoint_set_new(int size) {
    disjoint_set_t result = malloc(sizeof(disjoint_set_t));
    if(result == NULL) {
        return NULL;
    }
    int* data = malloc(size);
    if(data == NULL) {
        free(result);
        return NULL;
    }
    // setup set
    result->data = data;
    result->n_sets = size;
    result->size = size;

    // set them to zero
    for(int i = 0; i < size; i++) {
        data[i] = i;
    }
    return result;
}

int disjoint_set_find(const disjoint_set_t set, int i) {
    int root = i;
    // if is not root
    while(set->data[root] != root) {
        // set to parent
        root = set->data[root];
    }
    // Now, root is what we want

    // Next, set the parents of all parents of i to root
    while(set->data[i] != i) {
        // set to parent
        int parent = set->data[i];
        set->data[i] = root;
        i = parent;
    }
    return root;
}

int disjoint_set_union(disjoint_set_t set, int i, int j) {
    int root_i = disjoint_set_find(set, i);
    int root_j = disjoint_set_find(set, j);
    if(root_i == root_j) {
        return root_i;
    }
    set->n_sets -= 1;
    set->data[root_j] = root_i;
    // return value is the merged class
    return root_i;
}

void disjoint_set_delete(disjoint_set_t set) {
    free(set->data);
    free(set);
}
