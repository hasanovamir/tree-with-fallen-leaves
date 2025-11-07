#include "tree.h"

//--------------------------------------------------------------------------------

tree_err_t 
TreeInsert (TreeContext_t* TreeContext, tree_data_t val)
{
    if (TreeContext->size == 0) {
        TreeNode_t* NewNode = MyAlloc (TreeContext, 1);

        if (NewNode == NULL) {
            PRINTERR (TREE_ALLOC_ERR);
            return   (TREE_ALLOC_ERR);
        }

        NewNode->data = val;
        TreeContext->head = NewNode;
        TreeContext->size++;
    }
    else {
        if (TreeAddNode (TreeContext, TreeContext->head, val))
            return TREE_ALLOC_ERR;
    }

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeAddNode (TreeContext_t* TreeContext ,TreeNode_t* Node, tree_data_t val)
{
    DEBUG_ASSERT (Node != NULL);

    if (val <= Node->data) {
        if (Node->left) {
            TreeAddNode (TreeContext, Node->left, val);
        }
        else {
            TreeNode_t* NewNode = MyAlloc (TreeContext, 1);

            if (NewNode == NULL) {
                PRINTERR (TREE_ALLOC_ERR);
                return   (TREE_ALLOC_ERR);
            }

            NewNode->data = val;
            NewNode->idx = TreeContext->size;
            Node->left = NewNode;
            TreeContext->size++;
        }
    }
    else {
        if (Node->right) {
            TreeAddNode (TreeContext, Node->right, val);
        }
        else {
            TreeNode_t* NewNode = MyAlloc (TreeContext, 1);

            if (NewNode == NULL) {
                PRINTERR (TREE_ALLOC_ERR);
                return   (TREE_ALLOC_ERR);
            }

            NewNode->data = val;
            NewNode->idx = TreeContext->size;
            Node->right = NewNode;
            TreeContext->size++;
        }
    }

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------