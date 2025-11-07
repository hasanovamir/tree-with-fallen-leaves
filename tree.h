#ifndef TREE_H
#define TREE_H

//————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//————————————————————————————————————————————————————————————————————————————————

typedef int tree_data_t;

//————————————————————————————————————————————————————————————————————————————————

typedef enum
{
    TREE_SUCCESS,
    TREE_OPEN_FILE_ERR,
    TREE_SYS_FUNC_ERR,
    TREE_ALLOC_ERR,
} tree_err_t;

//————————————————————————————————————————————————————————————————————————————————

struct TreeNode_t {
    int         idx;
    tree_data_t data;
    TreeNode_t* left;
    TreeNode_t* right;
};

//————————————————————————————————————————————————————————————————————————————————

struct TreeContext_t {
    int         num_calls;
    int         src_size;
    int         src_cap;
    int         size;
    TreeNode_t* head;
    TreeNode_t* src;
};

//————————————————————————————————————————————————————————————————————————————————

void        MakeDumpTitle     (FILE* dot_file);
void        PrintNode         (const TreeNode_t* Node);
void        MakeDumpNode      (FILE* dot_file, TreeNode_t* Node);
void        MakeDumpEdge      (FILE* dot_file, TreeNode_t* Node);
tree_err_t  TreeStartFillHtml (void);
tree_err_t  TreeEndFillHtml   (void);
tree_err_t  TreeInit          (TreeContext_t* TreeContext);
tree_err_t  TreeInit          (TreeContext_t* TreeContext);
tree_err_t  TreeDump          (TreeContext_t* TreeContext);
TreeNode_t* MyAlloc           (TreeContext_t* TreeContext, int count);
tree_err_t  TreeInsert        (TreeContext_t* TreeContext, tree_data_t val);
tree_err_t  FillDotFile       (TreeContext_t* TreeContext, const char* file_name);
tree_err_t  TreeFillHtml      (TreeContext_t* TreeContext, const char* file_name);
tree_err_t  TreeAddNode       (TreeContext_t* TreeContext ,TreeNode_t* Node, tree_data_t val);

//————————————————————————————————————————————————————————————————————————————————

#ifndef N_DEBUG
#define DEBUG_ASSERT(cond)\
if (!cond)\
{\
    fprintf(stderr, "%s in %s:%d func:%s\n", #cond, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    exit(1);\
}
#else
#define DEBUG_ASSERT(cond) ;
#endif //N_DEBUG

//————————————————————————————————————————————————————————————————————————————————

#define PRINTERR(str)\
fprintf (stderr, "%s in %s:%d in %s", #str, __FILE__, __LINE__, __PRETTY_FUNCTION__);

//————————————————————————————————————————————————————————————————————————————————

#endif // TREE_H