#include "tree.h"

void putstr(void *str)
{
    unsigned int i = 0;
    char *s = (char*)str;

    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

t_btree *btree_create_node(void *item)
{
    t_btree *new;

    new = malloc(sizeof(t_btree));
    new->item = item;
    return new;
}

void btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
    if (root)
    {
        applyf(root->item);
        btree_apply_prefix(root->left, applyf);
        btree_apply_prefix(root->right, applyf);
    }
}

int main()
{
    t_btree *root = btree_create_node("1");
    t_btree *l = btree_create_node("0");
    t_btree *ll = btree_create_node("-1");
    t_btree *r = btree_create_node("2");
    t_btree *rr = btree_create_node("3");
    t_btree *lr = btree_create_node("0.5");

    root->left = l;
    root->right = r;
    l->left = ll;
    l->right = lr;
    r->right = rr;
    btree_apply_prefix(root, putstr);
    return (0);
}