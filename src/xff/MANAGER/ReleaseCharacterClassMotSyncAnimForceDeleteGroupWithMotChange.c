extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);
extern void isysDeleteGroupAllObj(void *);

static inline char *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (char *)object + 0x90;
    case 0x16: return (char *)object + 0x90;
    default: return 0;
    }
}

void ReleaseCharacterClassMotSyncAnimForceDeleteGroupWithMotChange(unsigned char *object)
{
    void *grp = characterClass(object) + 0xD96;
    void *o = 0;
    void **g;

    for (g = isysGroupForFirst(grp, 0); g != 0; g = isysGroupForNext(g, 0)) {
        o = *g;
        isysRequestDeleteObj(o);
    }
    if (o != 0)
        isysGroupForExit(o, 0);
    isysDeleteGroupAllObj(grp);
}
