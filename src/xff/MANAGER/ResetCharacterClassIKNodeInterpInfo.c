void ResetCharacterClassIKNodeInterpInfo(char *c)
{
    int i;
    int n;
    char *m = *(char **)(c + 0x358);
    if (m == 0)
        return;
    n = *(int *)(m + 4);
    for (i = 0; i < n; i++) {
        ((int *)*(int *)(c + 0x320))[i] = 0;
        ((int *)*(int *)(c + 0x324))[i] = 0;
    }
}
