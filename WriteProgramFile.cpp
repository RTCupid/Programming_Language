void WriteBase (node_t* crnt_node, FILE* file, int level)
{
    WriteTab (level, file);
    fprintf (file, "{");
    fprintf (file, "\"%s\"", crnt_node->text);

    if (crnt_node->left)
    {
        fprintf (file, "\n");

        WriteBase (crnt_node->left , file, level + 1);
        WriteBase (crnt_node->right, file, level + 1);
        WriteTab (level, file);
    }
    fprintf (file, "}\n");
    return;
}

void WriteTab (int level, FILE* file)
{
    for (int i = 1; i < level; i++)
    {
        assert (i < level);
        fprintf (file, "\t");
    }
}
