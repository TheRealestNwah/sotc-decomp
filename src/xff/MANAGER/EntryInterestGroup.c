extern void *DldSysUndefSymbol;
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
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
void EntryInterestGroup(void *owner, void *object, unsigned int *reference)
{
    char *resource = resourceData(reference);
    int *link = (int *)((char *)owner + 4);
    int *enabled = (int *)(resource + 0x34);
    int remaining = 15;
    do {
        if (*enabled++)
            isysAddGroupWithLinkParam(object, link, 0, 0);
        link++;
    } while (--remaining >= 0);
}
