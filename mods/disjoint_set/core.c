#include <stdlib.h>
#include "core.h"


disjoint_set_t disjoint_set_new(int size) {
    int step = sizeof(int);
    if(size <= 256) {
        step = 1;
    } else if(size <= 65536) {
        step = 2;
    } else {
        step = sizeof(int);
    }

    disjoint_set_t result = malloc(sizeof(struct _disjoint_set_t));
    if(result == NULL) {
        return NULL;
    }

    // setup set
    result->data = NULL;
    result->step = step;
    result->n_sets = size;
    result->size = size;
    if(size == 0) {
        return result;
    }

    result->data = malloc(size * step);
    if(result->data == NULL) {
        free(result);
        return NULL;
    }

    // set them to zero
    for(int i = 0; i < size; i++) {
        disjoint_raw_set(result, i, i);
    }
    return result;
}

int disjoint_raw_get(const disjoint_set_t set, int index) {
    if(set == NULL) {
        return -1;
    }
    if(set->data == NULL) {
        return -1;
    }
    if(index < 0 || index > set->size) {
        return -1;
    }
    if(set->step == sizeof(uint8_t)) {
        return (int)((uint8_t*)(set->data))[index];
    }
    if(set->step == sizeof(uint16_t)) {
        return (int)((uint16_t*)(set->data))[index];
    }
    return ((int*)(set->data))[index];
}

void disjoint_raw_set(const disjoint_set_t set, int index, int value) {
    if(set == NULL) {
        return;
    }
    if(set->data == NULL) {
        return;
    }
    if(index < 0 || index >= set->size) {
        return;
    }
    if(set->step == sizeof(uint8_t)) {
        ((uint8_t*)(set->data))[index] = (uint8_t)value;
    } else if(set->step == sizeof(uint16_t)) {
        ((uint16_t*)(set->data))[index] = (uint16_t)value;
    } else {
        ((int*)(set->data))[index] = value;
    }
}

int disjoint_set_find(const disjoint_set_t set, int i) {
    if(set == NULL) {
        return -1;
    }
    if(i < 0 || i >= set->size) {
        return -1;
    }
    int root = i;
    // if is not root
    while(disjoint_raw_get(set, root) != root) {
        // set to parent
        root = disjoint_raw_get(set, root);
    }
    // Now, root is what we want

    // Next, set the parents of all parents of i to root
    while(disjoint_raw_get(set, i) != i) {
        // set to parent
        int parent = disjoint_raw_get(set, i);
        disjoint_raw_set(set, i, root);
        i = parent;
    }
    return root;
}

int disjoint_set_union(disjoint_set_t set, int i, int j) {
    if(set == NULL) {
        return -1;
    }
    int root_i = disjoint_set_find(set, i);
    int root_j = disjoint_set_find(set, j);

    // invalid value
    if(root_i == -1 || root_j == -1) {
        return -1;
    }

    if(root_i == root_j) {
        return root_i;
    }
    set->n_sets -= 1;
    disjoint_raw_set(set, root_j, root_i);
    // return value is the merged class
    return root_i;
}

void disjoint_set_free(disjoint_set_t set) {
    if(set == NULL) {
        return;
    }
    if(set->data != NULL) {
        free(set->data);
    }
    free(set);
}
