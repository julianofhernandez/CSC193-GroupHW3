/*
* Stack containing race conditions
This program currently has a race condition and is not appropriate for a concurrent environment. Using 
Pthreads mutex locks (section 7.3.1), fix the race conditions. Test your now-thread-safe stack by creating 200 concurrent threads in main() that intermix pushing and popping values. 

-	Use a loop in main() to create all those threads. Apply all the things you've learned about creating 
and joining threads 
-	Write one testStack function, and use it as the entry point for each thread. 
-	The testStack function should intermix 3 push operations with 3 pop operations in a loop that 
executes 500 times. 
-	All threads use the same stack. 


*/
// Run using: gcc -pthread stack-ptr.c -o stack-ptr ; ./stack-ptr

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


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


void *testStack()
{
    printf("Running testStack!\n");
    pthread_exit(0);
}

int main(void)
{
    printf("Starting Group HW3\n");
    StackNode *top = NULL;

    push(5, &top);
    push(10,&top);
    pop (   &top);
    push(15,&top);
    pop (   &top);
    pop (   &top);
    push(20,&top);

    push(-5, &top);
    pop (    &top);
    push(-10,&top);
    pop (    &top);
    pop (    &top);
    push(-15,&top);
    pop (    &top);
    push(-20,&top);
    pthread_t thread;
    int error;
    error = pthread_create(&thread, NULL, &testStack, NULL);
    if (error)
        printf("Failed to create thread\n");
    else
        printf("Thread created\n");
    pthread_join(thread, NULL);
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
