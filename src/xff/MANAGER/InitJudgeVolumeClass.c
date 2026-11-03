#ifdef NONMATCHING /* 7 diffs: the groups pointer join lands in v1 instead of v0, so the original duplicates the store into the branch delay slot */
extern void *DldSysUndefSymbol;
extern void *iosMallocAlign(void *, int, int);
extern void isysInitGroup(void *);

typedef struct {
    int count;
    int *groups;
    void *data;
} JudgeVolumeWork;

static inline char *resourceModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    return module;
}

static inline int resourceCount(unsigned int *reference)
{
    char *module = resourceModule(reference);

    if (module && module != DldSysUndefSymbol)
        return *(int *)(module + 0xC);
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

void InitJudgeVolumeClass(JudgeVolumeWork *w, unsigned int *ref, void *heap)
{
    int n = resourceCount(ref);
    int i;

    w->count = n;
    w->groups = n != 0 ? iosMallocAlign(heap, n * 4, 4) : 0;
    w->data = resourceData(ref);
    for (i = 0; i < n; i++)
        isysInitGroup(&w->groups[i]);
}
#endif
