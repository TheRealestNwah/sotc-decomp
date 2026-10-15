extern void *getOptionDataAdrsAndSize(int *);
extern int opflowMcBootLoadedOptionData;
extern void *B_001885FC;
extern int memcmp(const void *, const void *, unsigned int);

int opflowCompareOptionData(void)
{
    int size;
    void *adr = getOptionDataAdrsAndSize(&size);
    if (opflowMcBootLoadedOptionData != 0)
        return 1;
    return memcmp(B_001885FC, adr, size);
}
