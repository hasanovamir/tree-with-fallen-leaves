#include "tree.h"

//--------------------------------------------------------------------------------

void 
PrintNode (const TreeNode_t* Node)
{
    DEBUG_ASSERT (Node != NULL);

    printf ("(");

    if (Node->left)
        PrintNode (Node->left);
    
    printf ("%d", Node->data);

    if (Node->right)
        PrintNode (Node->right);
    
    printf (")");
}

//--------------------------------------------------------------------------------

tree_err_t 
FillDotFile (TreeContext_t* TreeContext, const char* file_name)
{
    DEBUG_ASSERT (file_name != NULL);

    FILE* dot_file = fopen (file_name, "w");
    
    if (dot_file == NULL)
    {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   (TREE_OPEN_FILE_ERR);
    }

    MakeDumpTitle (dot_file);
    MakeDumpNode  (dot_file, TreeContext->head, 1);
    MakeDumpEdge  (dot_file, TreeContext->head);
    
    fprintf (dot_file, "}\n");

    fclose (dot_file);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

void 
MakeDumpTitle (FILE* dot_file)
{
    DEBUG_ASSERT (dot_file != NULL);

    fprintf (dot_file, "digraph ListDump {\n\trankdir=TB;\n\tnode [shape=Mrecord, fontname=\"Courier\"];\n\n\n\tgraph [splines=ortho]\n\toverlap=false;\n\n");
}

//--------------------------------------------------------------------------------
int inv_count = -1;
void 
MakeDumpNode (FILE* dot_file, TreeNode_t* Node, int rank)
{
    DEBUG_ASSERT (dot_file != NULL);

        fprintf (dot_file, "\tnode%d [label=\"{<idx> idx:%d | <data> data:%d }\", style=filled, color=aqua];\n", 
            Node->idx, Node->idx, Node->data);
    
    int new_rank = rank + 1, num_1 = 0, num_2 = 0;

    if (Node->left)
        MakeDumpNode (dot_file, Node->left, new_rank);
    // else {
    //     num_1 = inv_count;
    //     fprintf (dot_file, "\tnode_%d [label=\"{<idx> idx:%d | <data> data:0 }\", style=invis];\n", 
    //         inv_count, - inv_count);
    //     inv_count--;
    // }

    if (Node->right)
        MakeDumpNode (dot_file, Node->right, new_rank);
    // else {
    //     num_2 = inv_count;
    //     fprintf (dot_file, "\tnode_%d [label=\"{<idx> idx:%d | <data> data:0 }\", style=invis];\n", 
    //         inv_count, - inv_count);
    //     inv_count--;
    // }

        // fprintf (dot_file, "\t{rank=same;");

        // if (Node->left)
        //     fprintf (dot_file, " node%d;", Node->left->idx);
        // else
        //     fprintf (dot_file, " node_%d;", - num_1);

        // if (Node->right)
        //     fprintf (dot_file, " node%d;", Node->right->idx);
        // else
        //     fprintf (dot_file, " node_%d;", - num_2);

        // fprintf (dot_file, "}\n");
    
}

//--------------------------------------------------------------------------------

void 
MakeDumpEdge (FILE* dot_file, TreeNode_t* Node)
{
    DEBUG_ASSERT (dot_file != NULL);

    if (Node == NULL)
        return;

    if (Node->left) {
        fprintf (dot_file, "\tnode%d -> node%d [color=green];\n", Node->idx, Node->left->idx);
        MakeDumpEdge (dot_file, Node->left);
    }

    if (Node->right) {
        fprintf (dot_file, "\tnode%d -> node%d [color=green];\n", Node->idx, Node->right->idx);
        MakeDumpEdge (dot_file, Node->right);
    }
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeDump (TreeContext_t* TreeContext)
{
    TreeContext->num_calls++;

    char dot_file_name[20];
    char svg_file_name[20];
    char command[100];
    
    snprintf (dot_file_name, sizeof(dot_file_name), "dot/%s_%d.dot", "call", TreeContext->num_calls);
    snprintf (svg_file_name, sizeof(svg_file_name), "svg/%s_%d.svg", "call", TreeContext->num_calls);
    
    if (FillDotFile (TreeContext, dot_file_name))
    {
        return TREE_OPEN_FILE_ERR;
    }

    printf ("Generated DOT file:  %s\n", dot_file_name);
    
    snprintf (command, sizeof(command), "dot -Tsvg %s -o %s", dot_file_name, svg_file_name);

    int result = system(command);
    
    if (result == 0)
    {
        printf ("Generated SVG image: %s\n", svg_file_name);
    }
    else
    {
        PRINTERR (TREE_SYS_FUNC_ERR);
        return   (TREE_SYS_FUNC_ERR);
    }

    if (TreeFillHtml (TreeContext, svg_file_name))
        return TREE_OPEN_FILE_ERR;

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeStartFillHtml (void)
{
    FILE* html_file = fopen ("tree_dump.html", "w");

    if (html_file == NULL)
    {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   (TREE_OPEN_FILE_ERR);
    }

    fprintf (html_file, "<!DOCTYPE html>\n<html>\n<head>\n\t<title>LIST DUMP</title>\n</head>\n<body>\n");

    fclose (html_file);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeFillHtml (TreeContext_t* TreeContext, const char* file_name)
{
    FILE* html_file = fopen ("list_dump.html", "a");

    if (html_file == NULL)
    {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   (TREE_OPEN_FILE_ERR);
    }

    char string[500] = "";

    snprintf (string, 500, "\t<h2>CALL = #%d</h2>\n\t<p>HEAD = %p</p>\n\t<img src=\"%s\">\n\n", 
        TreeContext->num_calls, TreeContext->head, file_name);

    fprintf (html_file, string);

    fclose (html_file);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeEndFillHtml (void)
{
    FILE* html_file = fopen ("tree_dump.html", "a");

    if (html_file == NULL)
    {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   (TREE_OPEN_FILE_ERR);
    }

    fprintf (html_file, "</body>\n</html>");

    fclose (html_file);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------