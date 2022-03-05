#include "tree.h"
#include <stdio.h>

t_btree *btree_create_node(void *item)
{
    t_btree *new;

    new = malloc(sizeof(t_btree));
    new->item = item;
    return new;
}

int main()
{
    t_btree *node = btree_create_node("salut");

    printf("%s\n", (char*)node->item);
    free(node);
    return (0);
}