#include <stdio.h>
#include <stdlib.h>

// set implemented as sorted array
typedef struct s set;
set* new_set(int *iter, int n); // O(n log n)
int find(set *s, int k); // O(log n)
void insert(set *s, int k); // O(n)
int delete(set *s, int k); // O(n)
int find_min(set *s); // O(1)
int find_max(set *s); // O(1)
int find_previous(set *s, int k); // O(log n)
int find_next(set *s, int k); // O(log n)
int binary_search(int *iter, int k, int n); // O(log n)
void set_resize(set *s); // O(n);
void merge_sort(int *array, int l, int r, int n); // O(n log n)
void merge(int *array, int l, int r, int n); // O(n log n)

typedef struct s {
    int size;
    int length;
    int *set;
} set;

// create a new set
// assumes n > 0;
set* new_set(int *iter, int n) {
    int *new_iter;
    set *s;

    s = (set*) malloc(sizeof(set));
    if (s == NULL) {
        return NULL;
    }
    
    new_iter = (int*) malloc(sizeof(int) * n);
    if (new_iter == NULL) {
        free(s);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        new_iter[i] = iter[i];
    }
    merge_sort(new_iter, 0, n - 1, n);

    s->set = new_iter;
    s->size = n;
    s->length = n;

    return s;
}

// return the index of the element k
int find(set *s, int k) {
   return binary_search(s->set, k, s->length);
}

// insert a element in set at the ordered position
void insert(set *s, int x) {
    if (s->length == s->size) {
        set_resize(s);
    }

    int i;
    i = 0;
    while (i < s->length) {
        if (s->set[i] < x) {
            i++;
        }
    }

    int j;
    j = s->length;
    while (j > i) {
        s->set[j] = s->set[j - 1]; // shift right
        j--;
    }
    s->set[i] = x;
    s->length++;
}

// delete a element of set and return it
int delete(set *s, int k) {
    int index;

    index = find(s, k);
    if (index != -1) {
        int ret;

        ret = s->set[index];
        while (index < s->length - 1) {
            s->set[index] = s->set[index + 1];
            index++;
        }
        s->length--;

        return ret;
    }
}

// return the min element
int find_min(set *s) {
    return s->set[0];
}

// return the max element
int find_max(set *s) {
    return s->set[s->length - 1];
}

// return the antecessor of the k element
int find_previous(set *s, int k) {
    int previous = find(s, k) - 1;
    if (previous > 0) {
        return s->set[previous];
    }

    return -1;
}

// return the predecessor of the k element
int find_next(set *s, int k) {
    int next = find(s, k) + 1;
    if (next < s->length - 1) {
        return s->set[next];
    }

    return -1;
}

int binary_search(int *iter, int k, int n) {
    int m, l, r;

    l = 0;
    r = n - 1;
    while (l <= r) {
        m = (l + r) / 2;
        if (k == iter[m]) { return m; }
        else if (k < iter[m]) { r = m - 1; }
        else { l = m + 1; }
    }

    return -1;
}

void set_resize(set *s) {
    int *new_set;

    s->size *= 2;
    new_set = (int*) malloc(sizeof(int) * s->size);
    for (int i = 0; i < s->length; i++) {
        new_set[i] = s->set[i];
    }
    free(s->set);
    s->set = new_set;
}

void merge(int *array, int l, int r, int n) {
    int m;
    int i1, i2;
    int temp_array[n];
    
    for (int i = l; i <= r; i++) temp_array[i] = array[i];

    m = (l + r) / 2;
    i1 = l;
    i2 = m + 1;
    for (int curr = l; curr <= r; curr++) {
        if (i1 == m + 1) array[curr] = temp_array[i2++];
        else if (i2 > r) array[curr] = temp_array[i1++];
        else if (temp_array[i1] <= temp_array[i2]) array[curr] = temp_array[i1++];
        else array[curr] = temp_array[i2++];
    }
}

void merge_sort(int *array, int l, int r, int n) {
    if (l < r) {
        int m;
        
        m = (l + r) / 2;
        merge_sort(array, l, m, n);
        merge_sort(array, m + 1, r, n);
        merge(array, l, r, n);
    }
}