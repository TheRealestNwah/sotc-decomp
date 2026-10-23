extern void *DldSysUndefSymbol;

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

int chkMotionList(void *motion, char *list)
{
    int count = *(int *)(list + 0xC);
    unsigned int *refs = *(unsigned int **)(list + 0x10);
    int i;

    for (i = 0; i < count; i++, refs++) {
        if (motion == resourceData(refs))
            return 1;
    }
    return 0;
}
