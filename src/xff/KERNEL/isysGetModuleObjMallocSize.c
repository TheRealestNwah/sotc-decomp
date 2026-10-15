int isysGetModuleObjMallocSize(char *m)
{
    int *p;
    if (*(int *)(m + 0x2C) & 0x40000000)
        p = (int *)(*(int **)(m + 0x1C))[1] - 1;
    else
        p = *(int **)(m + 0x1C) - 1;
    return (**(int **)p & 0xFFFFFF) * 4;
}
