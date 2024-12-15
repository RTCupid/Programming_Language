#include <stdio.h>
#include <stdlib.h>

#include "../hdr/Enum.h"
#include "../hdr/ProgramFunc.h"
#include "../hdr/DumpProgram.h"
#include "../hdr/colors.h"

//-----------------------------------------------TREE-------------------------------------------------------------

void ProgramGraphviz (tree_t* expr, modelang_t mode)
{
    static int numpng = 111;
    if (mode == FRONTEND)
    {
        fprintf (expr->log_file, "<FONT SIZE=\"6\"><center>Program: Frontend</center><FONT SIZE=\"5\">\n\n");
    }
    else if (mode == BACKEND)
    {
        fprintf (expr->log_file, "<FONT SIZE=\"6\"><center>Program: Backend</center><FONT SIZE=\"5\">\n\n");
        numpng = 222;
    }
    printf (BLU "<%s>\n" RESET, expr->data);
    fprintf (expr->log_file, "<center>\"%s\"</center>\n", expr->data);

    MakeNameTableHTM (expr, mode);

    MakeDotFileGraphviz (expr);

    char namepng[5] = {};
    sprintf (namepng, "%d", numpng);
    numpng++;
    char systemCall[100] = {};
    sprintf (systemCall,"dot -Tpng bin/dot/Expression.dot -o bin/png/%s.png", namepng);
    //printf ("systemCall = <<%s>>\n", systemCall);

    system (systemCall);

    fprintf (expr->log_file, "<center><img src = %s.png ></center>\n\n", namepng);
}

void MakeNameTableHTM (tree_t* expr, modelang_t mode)
{
    fprintf (expr->log_file, "<center> Nametable </center>\n");
    fprintf (expr->log_file, "<center><table border= \"1\">\n");

    fprintf (expr->log_file, "\t<thead>\n");

    fprintf (expr->log_file, "\t\t<tr>\n"
                                "\t\t\t<th></th>\n"
                                "\t\t\t<th>Start position</th>\n");

    if (mode == FRONTEND)
    {
        fprintf (expr->log_file, "\t\t\t<th>Number of symbols</th>\n");
    }
    if (mode == BACKEND)
    {
        fprintf (expr->log_file, "\t\t\t<th>name</th>\n");
    }
    fprintf (expr->log_file, "\t\t</tr>\n");

    fprintf (expr->log_file, "</thead>\n");

    fprintf (expr->log_file, "<tbody>\n");

    //printf (RED "nametable_id = %lu\n" RESET, expr->nametable_id);
    for (size_t i = 0; i < expr->nametable_id; i++)
    {
        //printf (RED "i = %lu\n" RESET, i);
        fprintf (expr->log_file, "<tr>\n");

        fprintf (expr->log_file, "<td> %lu </td>\n", i);

        fprintf (expr->log_file, "<td> %p </td>\n", expr->nametable[i].start_pos);

        if (mode == FRONTEND)
        {
            fprintf (expr->log_file, "<td> %lu </td>\n", expr->nametable[i].n_symbols);
        }

        if (mode == BACKEND)
        {
            //printf (RED "<%s>\n" RESET, expr->nametable[i].name);
            fprintf (expr->log_file, "<td> %s </td>\n", expr->nametable[i].name);
        }

        fprintf (expr->log_file, "</tr>\n");
    }

    fprintf (expr->log_file, "</tbody>\n");

    fprintf (expr->log_file, "</table></center>\n" );
}

void MakeDotFileGraphviz (tree_t* expr)
{
    FILE* dot_file = fopen ("bin/dot/Expression.dot", "wt");
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
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#FFC9A5\"; label =  \"%c \" ];\n", node, (int)node->value);
    }
    else if (node->type == ST)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#0ec17f\"; label =  \"%c \" ];\n", node, (int)node->value);
    }
    else if (node->type == NUM)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#C88DC2\"; label =  \"%f \" ];\n", node, node->value);
    }
    else if (node->type == ID)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#FF898D\"; label =  \"%d \" ];\n", node, (int)node->value);
    }
}

//-----------------------------------------------DUMP-------------------------------------------------------------

void DiffDump (tree_t* tree, modelang_t mode)
{
    static int numpng = 1111;
    if (mode == FRONTEND)
    {
        fprintf (tree->log_file, "<FONT SIZE=\"6\"><center>Dump program: Frontend</center><FONT SIZE=\"5\">\n\n");
    }
    else if (mode == BACKEND)
    {
        fprintf (tree->log_file, "<FONT SIZE=\"6\"><center>Dump program: Frontend</center><FONT SIZE=\"5\">\n\n");
        numpng = 2222;
    }

    MakeDotFileDump (tree);

    char namepng[5] = {};
    sprintf (namepng, "%d", numpng);
    numpng++;
    char systemCall[100] = {};
    sprintf (systemCall,"dot -Tpng bin/dot/DiffDump.dot -o bin/png/%s.png", namepng);
    //printf ("systemCall = <<%s>>\n", systemCall);

    system (systemCall);

    fprintf (tree->log_file, "<center><img src = %s.png ></center>\n\n", namepng);

    //system (systemCall);
    //system ("dot -Tpng DiffDump.dot -o DiffDump.png");

    //fprintf (tree->log_file, "<center><img src = DiffDump.png ></center>\n\n");
}

void MakeDotFileDump (tree_t* tree)
{
    FILE* dot_file = fopen ("bin/dot/DiffDump.dot", "wt");

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

    PrintNodeDumpDot (dot_file, node, tree);

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

void PrintNodeDumpDot (FILE* dot_file, node_t* node, tree_t tree)
{
    if (node->type == OP)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\" #FFC9A5\"; "
            "label =  \"{node: %p | value: %c | type: OP | {<left>left: %p | <right>right: %p}  }\" ];\n",
            node, node, (int)node->value,  node->left, node->right);
        //fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#aed6dc\"; label =  \"%c \" ];\n", node, node->value);
    }
    else if (node->type == ST)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\" #0ec17f\"; "
            "label =  \"{node: %p | value: %c | type: ST | {<left>left: %p | <right>right: %p}  }\" ];\n",
            node, node, (int)node->value,  node->left, node->right);
        //fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#aed6dc\"; label =  \"%c \" ];\n", node, node->value);
    }
    else if (node->type == NUM)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#C88DC2\"; "
            "label =  \"{node: %p | value: %f | type: NUM | {<left>left: %p | <right>right: %p}  }\" ];\n",
            node, node, node->value,  node->left, node->right);

        //fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#ff9a8d\"; label =  \"%d \" ];\n", node, node->value);
    }
    else if (node->type == ID)
    {
        fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#FF898D\"; "
            "label =  \"{node: %p | nametable_id: %d | {start_pos: %p | n_symbols: %lu} | type: ID | {<left>left: %p | <right>right: %p}  }\" ];\n",
            node, node, (int)node->value, tree.nametable[(int)node->value].start_pos, tree.nametable[(int)node->value].n_symbols, node->left, node->right);

        //fprintf (dot_file, "\t node%p [shape=Mrecord; style=filled; color=\"#4a536b\"; label =  \"%c \" ];\n", node, node->value);
    }
}
