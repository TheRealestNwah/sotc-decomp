void resetExpressionLocalHeightDiff(char *c)
{
    int n = 0;
    int *d = *(int **)(c + 0x33C);
    char *m = *(char **)(c + 0x358);
    if (m != 0)
        n = *(int *)(m + 0x20);
    while (n-- != 0)
        *d++ = 0;
}
