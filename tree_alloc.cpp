#include "tree.h"

//--------------------------------------------------------------------------------

tree_err_t 
TreeInit (TreeContext_t* TreeContext)
{
    DEBUG_ASSERT (TreeContext != NULL);

    TreeContext->src = (TreeNode_t*) calloc (1000, sizeof (TreeNode_t));

    if (TreeContext->src == NULL)
    {
        PRINTERR (TREE_ALLOC_ERR);
        return   (TREE_ALLOC_ERR);
    }

    TreeContext->src_cap = 1000;

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

TreeNode_t*
MyAlloc (TreeContext_t* TreeContext, int count)
{
    DEBUG_ASSERT (TreeContext != NULL);

    if (TreeContext->src_size + count >= TreeContext->src_cap)
    {
        TreeNode_t* tmp = (TreeNode_t*) realloc (TreeContext->src, TreeContext->src_cap * 2);

        if (tmp == NULL) {
            PRINTERR (TREE_ALLOC_ERR);
            return NULL;
        }

        TreeContext->src      = tmp;
        TreeContext->src_cap *= 2;
    }

    TreeContext->src_size += count;

    return TreeContext->src + TreeContext->src_size - count;
}

//--------------------------------------------------------------------------------