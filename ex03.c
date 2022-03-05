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
        btree_apply_suffix(root->left, applyf);
        btree_apply_suffix(root->right, applyf);
        applyf(root->item);
    }
}

int main()
{
    t_btree *root = btree_create_node("13");
    t_btree *l = btree_create_node("9");
    t_btree *ll = btree_create_node("2");
    t_btree *r = btree_create_node("7");
    t_btree *rr = btree_create_node("15");
    t_btree *rrl = btree_create_node("17");
    t_btree *rl = btree_create_node("1");
    t_btree *lr = btree_create_node("11");
    t_btree *lrl = btree_create_node("28");

    root->left = l;
    root->right = r;
    l->left = ll;
    l->right = lr;
    lr->left = lrl;
    r->right = rr;
    rr->left = rrl;
    r->left = rl;
    btree_apply_suffix(root, putstr);
    return (0);
}