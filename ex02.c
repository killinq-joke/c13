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

void btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
    if (root)
    {
        btree_apply_infix(root->left, applyf);
        applyf(root->item);
        btree_apply_infix(root->right, applyf);
    }
}

void btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
    if (root)
    {
        applyf(root->item);
        btree_apply_prefix(root->right, applyf);
        btree_apply_prefix(root->left, applyf);
    }
}

int main()
{
    t_btree *root = btree_create_node("4");
    t_btree *l = btree_create_node("2");
    t_btree *ll = btree_create_node("1");
    t_btree *r = btree_create_node("5");
    t_btree *rr = btree_create_node("6");
    t_btree *lr = btree_create_node("3");

    root->left = l;
    root->right = r;
    l->left = ll;
    l->right = lr;
    r->right = rr;
    // btree_apply_prefix(root, putstr);
    btree_apply_infix(root, putstr);
    return (0);
}