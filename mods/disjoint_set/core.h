#ifndef __DISJOINT_SET_CORE_H__
#define __DISJOINT_SET_CORE_H__


/*
Union-Find algorithm, or the disjoint union structure is to classify n elements into several classes.
We represent them as a set of indices {0, 1, 2, ..., n}. At the beginning, they are seperated into
exactly n classes. Then, based on the pair-wise equivalence relation, i.e., we only know two elements
are in the same class or not, we gradually merge those classes.

We represent those classes as trees, whose nodes are just those indices of that class. At the beginning,
we have n trees, with the only node the element itself. If we know element i and element j are in the
same class, we set the parent node of j to i, making a new tree.

Note that we want to preserve the rule that two elements are of the same class iff they are in the same tree.
Thus, classes are represented by those tree roots and if you want to distinguish two elements, just take
their roots and compare. So, if you want to merge the class of element i and the class of element j,
you just find the root of j and set its parent to the root of i.

For example, a set of 5 elements.

At the beginning, we have 5 trees.
0   1   2   3   4

If you know 0, 1 are in the same class and 3, 4 are in the same class, you merge them into the same tree.
0   2   3
|       |
1       4

Next, if we know 4 and 1 are in the same class, we find the root of 4, i.e., 3, and the root of 1, i.e., 0;
then we set the parent of 0 to 3 as follows.

2   3
   / \
  0   4
  |
  1

In C, we can represent such a forest of trees as an array A[n] with the convention that A[i] is the parent
node of i and i is the root of a tree iff A[i] = i, and we always flatten the tree struct after each find operation.

2   3            2   3
   / \              /|\
  0   4   =>       1 0 4
  |
  1

Note that if an element is already a root, then it is safe to change it parent,
and if you change the parent of an element to the root, you will not break the disjoint union.
Those are the basis that we can flatten a tree.
*/

typedef struct _disjoint_set_t {
    int size;
    int n_sets;
    int* data;
}* disjoint_set_t;

disjoint_set_t disjoint_set_new(int size);
int disjoint_raw_get(const disjoint_set_t set, int index);
void disjoint_raw_set(const disjoint_set_t set, int index, int value);
int disjoint_set_find(const disjoint_set_t set, int i);
int disjoint_set_union(disjoint_set_t set, int i, int j);
void disjoint_set_free(disjoint_set_t set);

#endif
