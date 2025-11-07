#include "tree.h"

//--------------------------------------------------------------------------------

int 
main (void) 
{
    TreeStartFillHtml ();

    TreeContext_t TreeContext = {};

    do {
        if (TreeInit   (&TreeContext))
            break;
        if (TreeInsert (&TreeContext, 10))
            break;
        if (TreeInsert (&TreeContext, 15))
            break;
        if (TreeInsert (&TreeContext, 5))
            break;
        if (TreeInsert (&TreeContext, 4))
            break;
        if (TreeInsert (&TreeContext, 7))
            break;
        if (TreeInsert (&TreeContext, 3))
            break;
        if (TreeInsert (&TreeContext, 5))
            break;
        if (TreeInsert (&TreeContext, 20))
            break;
    } while (0);

    TreeDump (&TreeContext);
    TreeEndFillHtml ();

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------