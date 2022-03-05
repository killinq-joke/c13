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

void btree_insert_data(t_btree **root, void *item, int (*cmpf)(void *, void *))
{
    t_btree *current;
    t_btree *next;

    if (!root || !item || !cmpf)
        return ;
    current = *root;
    next = current;
    while (next)
    {
        current = next;
        if (cmpf(item, current->item) < 0)
            next = current->left;
        else
            next = current->right;
    }
    if (cmpf(item, current->item) < 0)
        current->left = btree_create_node(item);
    else
        current->right = btree_create_node(item);
}

int main()
{
    t_btree *root = btree_create_node("13");
    btree_insert_data(&root, "9", strcmp);
    btree_insert_data(&root, "2", strcmp);
    btree_insert_data(&root, "7", strcmp);
    btree_insert_data(&root, "15", strcmp);
    btree_insert_data(&root, "17", strcmp);
    btree_insert_data(&root, "1", strcmp);
    btree_insert_data(&root, "11", strcmp);
    btree_insert_data(&root, "28", strcmp);
    /*
                13
           1             9
              11     2      28
                  15   7
                   17               
    */
    // t_btree *l = btree_create_node("9");
    // t_btree *ll = btree_create_node("2");
    // t_btree *r = btree_create_node("7");
    // t_btree *rr = btree_create_node("15");
    // t_btree *rrl = btree_create_node("17");
    // t_btree *rl = btree_create_node("1");
    // t_btree *lr = btree_create_node("11");
    // t_btree *lrl = btree_create_node("28");

    // root->left = l;
    // root->right = r;
    // l->left = ll;
    // l->right = lr;
    // lr->left = lrl;
    // r->right = rr;
    // rr->left = rrl;
    // r->left = rl;
    btree_apply_prefix(root, putstr);
    return (0);
}