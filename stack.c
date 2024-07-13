#include <stdlib.h>

typedef struct s stack;
typedef struct n node;
stack* new_stack();
node* new_node(node *next, int element); 
void push(stack *s, int x); // O(1)
int pop(stack *s); // O(1)
int top(stack *s); // O(1)
int length(stack *s); // O(1)

typedef struct s {
    int lenght;
    node *top;
} stack;

typedef struct n {
    int element;
    struct n *next;
} node;

stack* new_stack() {
    stack *s;

    s = (stack*) malloc(sizeof(stack));
    if (s == NULL) {
        NULL;
    }
    s->top = NULL;
    s->lenght = 0;

    return s;
}

node* new_node(node *next, int element) {
    node *n;

    n = (node*) malloc(sizeof(node));
    if (n == NULL) {
        return NULL;
    }
    n->next = next;
    n->element = element;

    return n;
} 

void push(stack *s, int x) {
    node *n;

    n = new_node(s->top, x);
    s->top = n;
    s->lenght++;
}

int pop(stack *s) {
    if (s->top == NULL) {
        return -1;
    }
    int ret;
    node *n;

    ret = s->top->element;
    n = s->top;
    s->top = s->top->next;
    s->lenght--;
    free(n);

    return ret;
}

int top(stack *s) {
    if (s->top == NULL) {
        return -1;
    }

    return s->top->element;
}

int length(stack *s) {
    return s->lenght;
}