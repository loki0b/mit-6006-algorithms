#include <stdlib.h>

typedef struct q queue;
typedef struct n node;
queue* new_queue();
node* new_node();
void enqueue(queue *q, int x); // O(1)
int dequeue(queue *q); // O(1)
int front_value(queue *q); // O(1)
int length(queue *q); // O(1)

typedef struct q {
    node *front;
    node *rear;
    int length;
} queue;

typedef struct n {
    int element;
    struct n *next;
} node;

queue* new_queue() {
    queue *q;

    q = (queue*) malloc(sizeof(queue));
    if (q == NULL) {
        return NULL;
    }
    q->front = q->rear = new_node(NULL, 0);
    q->length = 0;

    return q;
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

void enqueue(queue *q, int x) {
    node *n;

    n = new_node(NULL, x);
    q->rear->element = n;
    q->rear = q->rear->next;
    q->length++;
}

int dequeue(queue *q) {
    if (q->front->next == NULL) {
        return -1;
    }
    int ret;
    node *n;

    ret = q->front->next->element;
    n = q->front->next;
    q->front->next = q->front->next->next;
    if (q->front->next == NULL) {
        q->rear = q->front;
    }
    q->length--;
    free(n);

    return ret;
}

int front_value(queue *q) {
    if (q->front->next == NULL) {
        return -1;
    }

    return q->front->next->element;
}

int length(queue *q) {
    return q->length;
}