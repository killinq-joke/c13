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
    next = *root;
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

void *btree_search_item(t_btree *root, void *data_ref, int (*cmpf)(void *, void *))
{
    t_btree *current;

    if (!root || !cmpf)
        return NULL;
    if (!cmpf(data_ref, root->item))
        return root;
    current = root;
    while (current)
    {
        if (cmpf(data_ref, current->item) < 0)
            current = current->left;
        else if (cmpf(data_ref, current->item) > 0)
            current = current->right;
        else
            return current;
    }
}

int btree_level_count(t_btree *root)
{
    if (!root)
        return (0);
    return btree_level_count(root->left) + btree_level_count(root->right) + 1;
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
    btree_apply_prefix(root, putstr);
    t_btree *searched = btree_search_item(root, "10", strcmp);

    printf("%p\n", searched);
    if (searched)
        printf("%s\n", searched->item);
    printf("tree len == %d\n", btree_level_count(root));
    return (0);
}