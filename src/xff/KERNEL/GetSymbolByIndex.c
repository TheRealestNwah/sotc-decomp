int GetSymbolByIndex(char *obj, int index)
{
    char *t = *(char **)(obj + 0x1C);

    return *(int *)(t + 0x2C) + *(int *)(*(char **)(t + 0x28) + (index + *(int *)(t + 0x40)) * 16);
}
