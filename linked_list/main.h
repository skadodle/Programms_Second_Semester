#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *pNext;
};

typedef struct List
{
    struct Node *head;
    int size;
} List;

void initialize_list(List *lst);

void push_front(List *lst, int data);
void push_back(List *lst, int data);
void insert(List *lst, int index, int data);

void pop_front(List *lst);
void pop_back(List *lst);
void del(List *lst, int index);

void index(List *lst, int index);

void print(List *lst);
void clear(List *lst);

#endif