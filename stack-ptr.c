/*
* Stack containing race conditions
This program currently has a race condition and is not appropriate for a concurrent environment. Using 
Pthreads mutex locks (section 7.3.1), fix the race conditions. Test your now-thread-safe stack by creating 200 concurrent threads in main() that intermix pushing and popping values. 

-	The testStack function should intermix 3 push operations with 3 pop operations in a loop that 
executes 500 times. 


*/
// Run using: gcc -pthread stack-ptr.c -o stack-ptr ; ./stack-ptr

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int THREAD_COUNT = 2; // Needs to be set to 500 before submitting
// Mutx stuff, counter will be swapped with the stack
pthread_mutex_t lock;

// Linked list node
typedef int value_t;
typedef struct Node
{
    value_t data;
    struct Node *next;
} StackNode;

// Stack function declarations
void    push    (value_t v, StackNode **top);
value_t pop     (           StackNode **top);
int     is_empty(           StackNode *top);


void *testStack() //Stack pointer needs to be passed here, use push and pop function as a sample
{
    printf("Running testStack!\n");
    pthread_mutex_lock(&lock);
    // Do 3 pushes and 3 pops
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}

int main(void)
{
    printf("Starting Group HW3\n");
    StackNode *top = NULL;

    push(-5, &top);
    pop (    &top);
    push(-10,&top);
    pop (    &top);
    pop (    &top);
    push(-15,&top);
    pop (    &top);
    push(-20,&top);

    pthread_t thread[THREAD_COUNT];
    int error;
    int i = 0;
    while (i < THREAD_COUNT) {
        thread[i] = pthread_create(&thread[i], NULL, &testStack, NULL);
        i++;
    }
    i = 0;
    while (i < THREAD_COUNT) {
        pthread_join(thread[i], NULL);
        i++;
    }
    return 0;
}


// Stack function definitions
void push(value_t v, StackNode **top)
{
    StackNode* new_node = malloc(sizeof(StackNode));

    new_node->data = v;
    new_node->next = *top;
    *top           = new_node;
}

value_t pop(StackNode **top)
{
    if (is_empty(*top)) return (value_t)0;

    value_t     data  = (*top)->data;
    StackNode * temp  = *top;
    *top              = (*top)->next;

    free(temp);

    return data;
}

int is_empty(StackNode *top) {
    if (top == NULL) return 1;
    else             return 0;
}
