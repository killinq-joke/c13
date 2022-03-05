#ifndef TREE_H
# define TREE_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef struct s_btree t_btree;

typedef struct  s_btree
{
    void *item;
    t_btree *left;
    t_btree *right;
}               t_btree;

#endif