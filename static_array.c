#include <stdlib.h>
#include <stdio.h>

// sequence implemented as static array
typedef struct s_a static_array;
static_array* new_static_array(int size);
int get_at(static_array *s_a, int i);
void set_at(static_array *s_a, int i, int x);
void insert_at(static_array *s_a, int i, int x);
void delete_at(static_array *s_a, int i);
void insert_first(static_array *s_a, int x);
void delete_first(static_array *s_a);
void insert_last(static_array *s_a, int x);
void delete_last(static_array *s_a);
void insert_resize(static_array *s_a);
void delete_resize(static_array *s_a);
int length(static_array *s_a);

typedef struct s_a {
    int size;
    int *sequence; 
} static_array;

// create a new static array data structure
// the user will need input the n elements in the array to build
static_array* new_static_array(int size) {
    static_array *s_a;

    s_a = (static_array*) malloc(sizeof(static_array));
    if (s_a == NULL) {
        return NULL;
    }
    s_a->size = size;
    s_a->sequence = (int*) malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &(s_a->sequence[i]));
    }

    return s_a;
}

// resize the size of sequence to n + 1
void insert_resize(static_array *s_a) {
    int *new_sequence;

    new_sequence = (int*) malloc(sizeof(int) * (s_a->size + 1));
    for (int i = 0; i < s_a->size; i++) {
        new_sequence[i] = s_a->sequence[i];
    }
    free(s_a->sequence);
    s_a->size++;
    s_a->sequence = new_sequence;
}

// resize the size of sequence to n - 1
void delete_resize(static_array *s_a) {
    int *new_sequence;

    new_sequence = (int*) malloc(sizeof(int) * (s_a->size - 1));
    for (int i = 0; i < s_a->size; i++) {
        new_sequence[i] = s_a->sequence[i];
    }
    free(s_a->sequence);
    s_a->size--;
    s_a->sequence = new_sequence;
}

// get an element at the i-th position
int get_at(static_array *s_a, int i) {
    if (i >= 0 && i < s_a->size) {
        return s_a->sequence[i];
    }
}

// set an element at the i-th position
void set_at(static_array *s_a, int i, int x) {
    if (i >= 0 && i < s_a->size) {
        s_a->sequence[i] = x;
    }
}

// resize sequence and shift right then
// insert an element in the i-th position
void insert_at(static_array *s_a, int i, int x) {
    if (i >= 0 && i <= s_a->size) {
        int aux_i;

        insert_resize(s_a);

        aux_i = s_a->size;
        while (aux_i - 1 > i) {
            s_a->sequence[aux_i] = s_a->sequence[aux_i - 1]; // shift right
            aux_i--;
        }
        s_a->sequence[i] = x;
    }
}

// shift left and overwrite the i-th position (delete) then
// resize sequence. does not return the element
void delete_at(static_array *s_a, int i) {
    if (i >= 0 && i <= s_a->size - 1){
        while (i < s_a->size - 1) {
            s_a->sequence[i] = s_a->sequence[i + 1]; // shift left
            i++;
        }

        delete_resize(s_a);
    }
}

// insert an element at the first position of the array
void insert_first(static_array *s_a, int x) {
    insert_at(s_a, 0, x);
}

// delete the first element of the sequence
void delete_first(static_array *s_a) {
    delete_at(s_a, 0);
}

// insert an element at the last position of the sequence
void insert_last(static_array *s_a, int x) {
    insert_at(s_a, s_a->size, x);
}

// delete the last element of the sequence
void delete_last(static_array *s_a) {
    delete_at(s_a, s_a->size - 1);
}

int length(static_array *s_p) {
    return s_p->size;
}