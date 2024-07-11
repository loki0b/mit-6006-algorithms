#include <stdlib.h>
#include <stdio.h>

// sequence implemented as single linked list
typedef struct s_l linked_list;
typedef struct n node;
linked_list* new_linked_list(); // O(1)
node* new_node(node *next, int element); // O(1)
int get_at(linked_list *s_l, int i); // O(n)
void set_at(linked_list *s_l, int i, int x); // O(n)
void insert_at(linked_list *s_l, int i, int x); // O(n)
void delete_at(linked_list *s_l, int i); // O(n)
void insert_first(linked_list *s_l, int x); // O(1)
void delete_first(linked_list *s_l); // O(1)
void insert_last(linked_list *s_l, int x); // O(1) <- its O(n) if does not have the tail
void delete_last(linked_list *s_l); // O(1) <- its O(n) if does not have the tail
void move_cursor(linked_list *s_l, int i); // O(n)
int length(linked_list *s_l); // O(1)

typedef struct s_l {
    node *head;
    node *tail;
    node *curr;
    int size;
} linked_list;

typedef struct n {
    int element;
    struct n *next;
} node;

linked_list* new_linked_list() {
    linked_list *s_l;

    s_l = (linked_list*) malloc(sizeof(linked_list));
    if (s_l == NULL) {
        return NULL;
    }
    s_l->head = s_l->tail = s_l->curr = new_node(NULL, 0);
    s_l->size = 0;

    return s_l;
}

node* new_node(node *next, int element) {
    node *n;

    n = (node*) malloc(sizeof(node));
    if (n == NULL) {
        return NULL;
    }
    n->element = element;
    n->next = next;

    return n;
}

// return the i-th element
int get_at(linked_list *s_l, int i) {
    if (i >= 0 && i < s_l->size) {
        move_cursor(s_l, i);

        return s_l->curr->next->element;
    }

    return -1;
}

// set an element at the i-th position
void set_at(linked_list *s_l, int i, int x) {
    if (i >= 0 && i < s_l->size) {
        node *curr;

        curr = s_l->head;
        move_cursor(s_l, i);
        curr->next->element = x;
    }
}

// insert a new element at the i-th position
void insert_at(linked_list *s_l, int i, int x) {
    if (i >= 0 && i <= s_l->size) {
        node *n;

        move_cursor(s_l, i);
        n = new_node(s_l->curr->next, x);
        if (n != NULL) {
            s_l->curr->next = n;
            if (s_l->tail == s_l->curr) {
                s_l->tail = s_l->curr->next;
            }
            s_l->size++;
        }
    } 
}

void delete_at(linked_list *s_l, int i) {
    if (i >= 0 && i < s_l->size) {
        node *n;

        move_cursor(s_l, i);
        if (s_l->curr->next == s_l->tail) {
            s_l->tail = s_l->curr;
        }
        n = s_l->curr->next;
        s_l->curr->next = s_l->curr->next->next;
        free(n);
        s_l->size--;
    }
}

// insert an element at the first position
void insert_first(linked_list *s_l, int x) {
    insert_at(s_l, 0, x);
}

// delete an element at the first position
void delete_first(linked_list *s_l) {
    delete_at(s_l, 0);
}

// insert an element at the last position
void insert_last(linked_list *s_l, int x) {
    insert_at(s_l, s_l->size, x);
}

// delete the last element
void delete_last(linked_list *s_l) {
    delete_at(s_l, s_l->size - 1);
}

// move cursor to i-th - 1 position
void move_cursor(linked_list *s_l, int i) {
    int j;

    s_l->curr = s_l->head;
    j = 0;
    while (j < i) {
        s_l->curr = s_l->curr->next;
        j++;
    }
}

int length(linked_list *s_l) {
    return s_l->size;
}