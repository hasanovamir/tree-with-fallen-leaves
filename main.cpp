#include "tree.h"

//--------------------------------------------------------------------------------

int 
main (void) 
{
    TreeStartFillHtml ();
    TreeNode_t Node_7 = {.idx = 7, .data = 52};
    TreeNode_t Node_6 = {.idx = 6, .data = 15};
    TreeNode_t Node_5 = {.idx = 3, .data = 5};
    TreeNode_t Node_4 = {.idx = 4, .data = 8};
    TreeNode_t Node_3 = {.idx = 2, .data = 7, .left = &Node_5, .right = &Node_4};
    TreeNode_t Node_2 = {.idx = 5, .data = 20, .left = &Node_6, .right = &Node_7};
    TreeNode_t Node_1 = {.idx = 1,.data = 10, .left = &Node_3, .right = &Node_2};

    TreeContext_t TreeContext = {.size = 5, .head = &Node_1};

    PrintNode (&Node_1);

    TreeDump (&TreeContext);
    TreeEndFillHtml ();

    return EXIT_SUCCESS;
}