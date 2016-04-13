#include <stdio.h>
#include <stdlib.h>

/* type node */
typedef struct node
{
    void* data;         // data member
    struct node* next;  // pointer to the next node (forward)
    struct node* prev;  // pointer to the previous node (backward)
} node;

/* type list */
typedef struct list
{
    node* head; // pointer to the first node (head)
    node* tail; // pointer to the last node (tail)
} list;

/* */
void add_to_front(void* data, list* ls)
{
    node* n = (node*)calloc(1, sizeof(node));   // allocate memory for the node
    
    n->data = data;         // set the new node's data member to the data argument
    n->next = ls->head;     // point the new node forward to the old head
    n->prev = NULL;         // point the new node backward to NULL
    if (!ls->head)
        ls->tail = n;       // set list's tail pointer to the new node
    else
        ls->head->prev = n; // point the old head backward to the new node
    ls->head = n;           // set list's head pointer to the new node
}

/* */
void add_to_back(void* data, list* ls)
{
    node* n = (node*)calloc(1, sizeof(node));   // allocate memory for the node
    
    n->data = data;         // set the new node's data member to the data argument
    n->prev = ls->tail;     // point the new node backward to the old tail
    n->next = NULL;         // point the new node forward to NULL
    if (!ls->head)
        ls->head = n;       // set list's head pointer to the new node
    else
        ls->tail->next = n; // point the old tail forward to the new node
    ls->tail = n;           // set list's tail pointer to the new node
}

void* remove_from_front(list* ls)
{
    void* data = ls->head->data; // cache the data of the node to remove
    free(ls->head);              // free the memory used by the removed node
    ls->head = ls->head->next;   // set list's head pointer to the next node
    return data;
}

void* remove_from_back(list* ls)
{
    void* data = ls->tail->data; // cache the data of the node to remove
    free(ls->tail);              // free the memory used by the removed node
    ls->tail = ls->tail->prev;   // set list's tail pointer to the prev node
    return data;
}

void transfer(void* a1[], void* a2[], int len, void (*add)(void*, list*), void* (*rm)(list*))
{
    list* ls = (list*)calloc(1, sizeof(list));
    for (int i = 0; i < len; i++)
    {
        (add)(&a1[i], ls);
    }
    for (int i = 0; i < len; i++)
    {
        a2[i] = (rm)(ls);
    }
    for (int i = 0; i < len; i++)
    {
        printf("%d ", *a2[i]);
    }
}

/* */
int main()
{
    //list* ls = (list*)calloc(1, sizeof(list));
    //node* head = (node*)calloc(1, sizeof(node));
    //node* tail = (node*)calloc(1, sizeof(node));
    
    void* a1[5] = {1, 2, 3, 4, 5};
    void* a2[5];

    //add_to_back((int*)1, ls);
    //add_to_back((int*)2, ls);
    //add_to_back((int*)3, ls);

    transfer(a1, a2, 5, add_to_back, remove_from_front);

    return(0);
}