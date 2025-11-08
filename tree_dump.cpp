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
    MakeDumpNode  (dot_file, TreeContext->head);
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

    char title[] = 

R"(digraph ListDump {
    rankdir=TB;
    node [shape=Mrecord, fontname="Courier"];

    graph [splines=ortho]
    overlap=false;
    
)";

    fprintf (dot_file, title);
}

//--------------------------------------------------------------------------------

void 
MakeDumpNode (FILE* dot_file, TreeNode_t* Node)
{
    DEBUG_ASSERT (dot_file != NULL);

    fprintf (dot_file, "\tnode%d [label=\"{<data> data:%d | <idx> idx:%d | <ptr> ptr:%p | {<left> left=%p | <right> right=%p } }\", style=filled, color=lime];\n", 
        Node->idx, Node->data, Node->idx, Node, Node->left, Node->right);

    if (Node->left)
        MakeDumpNode (dot_file, Node->left);
    if (Node->right)
        MakeDumpNode (dot_file, Node->right);
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

    char dot_file_name[MAXFILENAMESIZE];
    char svg_file_name[MAXFILENAMESIZE];
    char command[MAXCOMMANDSIZE];
    
    snprintf (dot_file_name, MAXFILENAMESIZE, "dot/%s_%d.dot", "call", TreeContext->num_calls);
    snprintf (svg_file_name, MAXFILENAMESIZE, "svg/%s_%d.svg", "call", TreeContext->num_calls);
    
    if (FillDotFile (TreeContext, dot_file_name))
    {
        return TREE_OPEN_FILE_ERR;
    }

    printf ("\nGenerated DOT file:  %s\n", dot_file_name);
    
    snprintf (command, sizeof(command), "dot -Tsvg %s -o %s", dot_file_name, svg_file_name);

    int result = system(command);
    
    if (result == 0)
    {
        printf ("Generated SVG image: %s\n\n", svg_file_name);
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
    FILE* html_file = fopen ("tree_dump.html", "a");

    if (html_file == NULL)
    {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   (TREE_OPEN_FILE_ERR);
    }

    char string[MAXSTRINGSIZE] = "";

    snprintf (string, MAXSTRINGSIZE, "\t<h2>CALL = #%d</h2>\n\t<p>HEAD = %p</p>\n\t<img src=\"%s\">\n\n", 
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