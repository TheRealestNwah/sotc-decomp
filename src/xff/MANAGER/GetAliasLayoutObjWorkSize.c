extern int GetClothWorkSize(int);

int GetAliasLayoutObjWorkSize(char *o)
{
    int r = 0;
    char *a = *(char **)(o + 0xC);
    if (a != 0)
        r = GetClothWorkSize(*(int *)(*(char **)(a + 8) + 0x20));
    return r;
}
