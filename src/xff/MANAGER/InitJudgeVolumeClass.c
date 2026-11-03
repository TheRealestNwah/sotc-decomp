#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
extern void *DldSysUndefSymbol;
extern void *iosMallocAlign(void *heap, int size, int align);
extern void isysInitGroup(void *group);

typedef struct {
    int count;
    int *groups;
    void *data;
} JudgeVolumeClass;

static inline char *resourceModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    if (offset)
        return *(char **)((char *)reference - offset);
    return 0;
}

static inline void *resourceData(unsigned int *reference)
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

void InitJudgeVolumeClass(JudgeVolumeClass *jv, unsigned int *reference, void *heap)
{
    char *module = resourceModule(reference);
    int count;
    int i;

    if (module && module != DldSysUndefSymbol)
        count = *(int *)(module + 0xC);
    else
        count = 0;
    jv->count = count;
    jv->groups = count ? iosMallocAlign(heap, count * 4, 4) : 0;
    jv->data = resourceData(reference);
    for (i = 0; i < count; i++)
        isysInitGroup(&jv->groups[i]);
}
#endif
