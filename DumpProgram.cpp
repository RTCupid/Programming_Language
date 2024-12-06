#include <stdio.h>
#include <stdlib.h>

#include "MyLanguage.h"
#include "DumpProgram.h"
#include "colors.h"

//-----------------------------------------------TREE-------------------------------------------------------------

void ProgramGraphviz (tree_t* expr)
{
    fprintf (expr->log_file, "<FONT SIZE=\"6\"><center>Programm: expression</center><FONT SIZE=\"5\">\n\n");

    MakeDotFileGraphviz (expr);

    static int numpng = 111;

    char namepng[4] = {};
    sprintf (namepng, "%d", numpng);
    numpng++;
    char systemCall[100] = {};
    sprintf (systemCall,"dot -Tpng Expression.dot -o %s.png", namepng);
    //printf ("systemCall = <<%s>>\n", systemCall);

    system (systemCall);

    fprintf (expr->log_file, "<center><img src = %s.png ></center>\n\n", namepng);
}

void MakeDotFileGraphviz (tree_t* expr)
{
    FILE* dot_file = fopen ("Expression.dot", "wt");
    VerifyOpenFile (dot_file, "MakeDotFileGraphviz");

    fprintf (dot_file, "digraph G {\n");
    fprintf (dot_file, "\trankdir = HR;\n");
    fprintf (dot_file, "\tbgcolor=\"#F7F9FB\"\n");


    PrintGraphviz (*expr, expr->root, dot_file);

    fprintf (dot_file, "}\n");
    fclose (dot_file);
}

void PrintGraphviz (tree_t expr, node_t* node, FILE* dot_file)
{
    if (!node)
    {
        return;
    }

    PrintNodeDot (dot_file, node);

    if (node->left)
    {
        fprintf (dot_file, "\t node%p -> node%p [ style=bold; weight=1000; ];\n", node, node->left);
    }

    if (node->right)
    {
        fprintf (dot_file, "\t node%p -> node%p [ style=bold; weight=1000; ];\n", node, node->right);
    }

    /*......LEFT......*/
    PrintGraphviz (expr, node->left, dot_file);

    /*......RIGHT......*/
    PrintGraphviz (expr, node->right, dot_file);
}

void PrintNodeDot (FILE* dot_file, node_t* node)
{
    if (node->type == OP)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#aed6dc\"; label =  \"%c \" ];\n", node, (int)node->value);
    }
    if (node->type == NUM)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#ff9a8d\"; label =  \"%f \" ];\n", node, node->value);
    }
    if (node->type == VAR)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#4a536b\"; label =  \"%c \" ];\n", node, (int)node->value);
    }
}

//-----------------------------------------------DUMP-------------------------------------------------------------

void DiffDump (tree_t* tree)
{
    fprintf (tree->log_file, "<FONT SIZE=\"6\"><center>Dump Differentiator!:</center><FONT SIZE=\"5\">\n\n");

    MakeDotFileDump (tree);

    static int numpng = 1111;

    char namepng[5] = {};
    sprintf (namepng, "%d", numpng);
    numpng++;
    char systemCall[100] = {};
    sprintf (systemCall,"dot -Tpng DiffDump.dot -o %s.png", namepng);
    //printf ("systemCall = <<%s>>\n", systemCall);

    system (systemCall);

    fprintf (tree->log_file, "<center><img src = %s.png ></center>\n\n", namepng);

    //system (systemCall);
    //system ("dot -Tpng DiffDump.dot -o DiffDump.png");

    //fprintf (tree->log_file, "<center><img src = DiffDump.png ></center>\n\n");
}

void MakeDotFileDump (tree_t* tree)
{
    FILE* dot_file = fopen ("DiffDump.dot", "wt");

    fprintf (dot_file, "digraph G {\n");
    fprintf (dot_file, "\trankdir = HR;\n");
    fprintf (dot_file, "\tbgcolor=\"#F7F9FB\"\n");

    PrintDump (*tree, tree->root, dot_file);

    fprintf (dot_file, "}\n");
    fclose (dot_file);
}

void PrintDump (tree_t tree, node_t* node, FILE* dot_file)
{
    if (!node)
    {
        return;
    }

    PrintNodeDumpDot (dot_file, node);

    if (node->left)
    {
        fprintf (dot_file, "\t node%p:<left> -> node%p [style=bold; weight=1000; ];\n", node, node->left);
    }
    if (node->right)
    {
        fprintf (dot_file, "\t node%p:<right> -> node%p [style=bold; weight=1000; ];\n", node, node->right);
    }

    /*......LEFT......*/
    PrintDump (tree, node->left, dot_file);

    /*......RIGHT......*/
    PrintDump (tree, node->right, dot_file);
}

void PrintNodeDumpDot (FILE* dot_file, node_t* node)
{
    if (node->type == OP)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#aed6dc\"; "
            "label =  \"{node: %p | value: %c | type: OP | {<left>left: %p | <right>right: %p}  }\" ];\n",
            node, node, (int)node->value,  node->left, node->right);
        //fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#aed6dc\"; label =  \"%c \" ];\n", node, node->value);
    }
    if (node->type == NUM)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#ff9a8d\"; "
            "label =  \"{node: %p | value: %f | type: NUM | {<left>left: %p | <right>right: %p}  }\" ];\n",
            node, node, node->value,  node->left, node->right);

        //fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#ff9a8d\"; label =  \"%d \" ];\n", node, node->value);
    }
    if (node->type == VAR)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#4a536b\"; "
            "label =  \"{node: %p | value: %c | type: VAR | {<left>left: %p | <right>right: %p}  }\" ];\n",
            node, node, (int)node->value,  node->left, node->right);

        //fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#4a536b\"; label =  \"%c \" ];\n", node, node->value);
    }
}
