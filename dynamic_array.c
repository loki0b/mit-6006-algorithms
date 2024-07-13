#include <stdlib.h>
#include <stdio.h>

// sequence implemented as dynamic array
typedef struct d_a dynamic_array;
dynamic_array* new_dynamic_array(int size); // O(n)
int get_at(dynamic_array *d_a, int i); // O(1)
void set_at(dynamic_array *d_a, int i, int x); // O(1)
void insert_at(dynamic_array *d_a, int i, int x); // O(n)
void delete_at(dynamic_array *d_a, int i); // O(n)
void insert_first(dynamic_array *d_a, int x); // O(n)
void delete_first(dynamic_array *d_a); // O(n)
void insert_last(dynamic_array *d_a, int x); // O(1) amortized
void delete_last(dynamic_array *d_a); // O(1) amortized
void array_resize(dynamic_array *d_a); // O(n)
int length(dynamic_array *d_a); // O(1)

typedef struct d_a {
    int size; // actual size of array
    int length; // number of elements
    int *sequence;
} dynamic_array;

// create a new dynamic array data structure
// the user will need input the n elements in the array to build
// assumes n > 0
dynamic_array* new_dynamic_array(int size) {
    dynamic_array *d_a;

    d_a = (dynamic_array*) malloc(sizeof(dynamic_array));
    if (d_a == NULL) {
        return NULL;
    }

    d_a->size = d_a->length = size;
    d_a->sequence = (int*) malloc(sizeof(int) * size);
    if (d_a->sequence == NULL) {
        free(d_a);
        return NULL;
    }
    for (int i = 0; i < d_a->length; i++) {
        scanf("%d", &(d_a->sequence[i]));
    }

    return d_a;
}

// return the i-th element
int get_at(dynamic_array *d_a, int i) {
    if (i >= 0 && i < d_a->length) {
        return d_a->sequence[i];
    }
}

// set the i-th element
void set_at(dynamic_array *d_a, int i, int x) {
    if (i >= 0 && i < d_a->length) {
        d_a->sequence[i] = x;
    }
}

// insert an element at the i-th position
// if the array is full then resize
void insert_at(dynamic_array *d_a, int i, int x) {
    if (d_a->length == d_a->size) {
        array_resize(d_a);
    }
    int aux_i;

    aux_i = d_a->length;
    while (aux_i > i) {
        d_a->sequence[aux_i] = d_a->sequence[aux_i - 1]; // shift right
        aux_i--;
    }
    d_a->sequence[i] = x;
    d_a->length++;
}

// delete an element at the i-th posistion
// does not return the element
void delete_at(dynamic_array *d_a, int i) {
    if (i >= 0 && i < d_a->length){
        while (i < d_a->length - 1) {
            d_a->sequence[i] = d_a->sequence[i + 1]; // shift left
            i++;
        }
        d_a->length--;
    }
}

// insert an element at the first position of the sequence
void insert_first(dynamic_array *d_a, int x) {
    insert_at(d_a, 0, x);
}

// delete the first element of the sequence
void delete_first(dynamic_array *d_a) {
    delete_at(d_a, 0);
}

// insert an element at the last position of the sequence
void insert_last(dynamic_array *d_a, int x) {
    insert_at(d_a, d_a->length, x);
}

// delete the last element of the sequence
void delete_last(dynamic_array *d_a) {
    d_a->length--;
}

// resize the sequence to a constat factor of 2
// assumes sequence size at least 1
void array_resize(dynamic_array *d_a) {
    int *new_sequence;

    d_a->size *= 2;
    new_sequence = (int*) malloc(sizeof(int) * d_a->size);
    for (int i = 0; i < d_a->length; i++) {
        new_sequence[i] = d_a->sequence[i];
    }
    free(d_a->sequence);
    d_a->sequence = new_sequence;
} 

int length(dynamic_array *d_a) {
    return d_a->length;
}