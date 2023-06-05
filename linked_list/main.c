#include "main.h"

int main()
{
    List lst;
    initialize_list(&lst);

    push_front(&lst, 15);
    push_back(&lst, 7);
    insert(&lst, 1, 23);
    push_front(&lst, 15);
    push_back(&lst, 7);
    insert(&lst, 1, 23);
    push_front(&lst, 15);
    push_back(&lst, 7);
    insert(&lst, 1, 23);

    print(&lst);

    printf("\n\n");

    pop_front(&lst);
    del(&lst, 3);
    pop_back(&lst);

    print(&lst);

    clear(&lst);
}
