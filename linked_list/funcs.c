#include "main.h"

void initialize_list(List *lst)
{
    lst->size = 0;
    lst->head = NULL;

    printf("Initialized single_linked_list!\n");
}

void push_front(List *lst, int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->pNext = lst->head;
    lst->head = new_node;
    lst->size++;
}

void push_back(List *lst, int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->pNext = NULL;
    if (lst->size == 0)
    {
        lst->head = new_node;
    }
    else
    {
        struct Node *current = lst->head;

        while (current->pNext != NULL)
        {
            current = current->pNext;
        }
        current->pNext = new_node;
    }
    lst->size++;
}

void insert(List *lst, int index, int data)
{
    if (index < 0 || index > lst->size)
    {
        printf("Error! Invalid index.\n");
        return;
    }
    if (index == 0)
    {
        push_front(lst, data);
        return;
    }
    if (index == lst->size)
    {
        push_back(lst, data);
        return;
    }
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    struct Node *current_node = lst->head;
    for (int i = 0; i < index - 1; i++)
    {
        current_node = current_node->pNext;
    }
    new_node->pNext = current_node->pNext;
    current_node->pNext = new_node;
    lst->size++;
}

void pop_front(List *lst)
{
    if (lst->size == 0)
    {
        printf("Error: List is empty");
        return;
    }
    struct Node *temp = lst->head;
    lst->head = lst->head->pNext;
    free(temp);
    lst->size--;
}

void pop_back(List *lst)
{
    del(lst, lst->size - 1);
}

void del(List *lst, int index)
{
    if (index < 0 || index >= lst->size)
    {
        printf("Error: Invalid index");
        return;
    }
    if (index == 0)
    {
        pop_front(lst);
        return;
    }
    struct Node *current_node = lst->head;
    for (int i = 0; i < index - 1; i++)
    {
        current_node = current_node->pNext;
    }
    struct Node *temp = current_node->pNext;
    current_node->pNext = temp->pNext;
    temp->pNext = NULL;
    free(temp);
    lst->size--;
}

void index(List *lst, int index)
{
    if (index < 0 || index >= lst->size)
    {
        printf("Error!\n");
        return;
    }
    struct Node *cur = lst->head;
    for (int i = 0; i < index; i++)
    {
        cur = cur->pNext;
    }

    printf("%d\n", cur->data);
}

void print(List *lst)
{
    for (int i = 0; i < lst->size; i++)
    {
        index(lst, i);
    }
}

void clear(List *lst)
{
    while (lst->size)
    {
        pop_front(lst);
    }
}