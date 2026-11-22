extern void ChangeCharacterObjControlTarget(unsigned char *, unsigned char *);
extern void ResetCharacterClassPositionMemoryInfo(char *);
extern void DeleteTwoWayLink(void *);
extern void iosFree(void *);
extern void DeleteAllTwoWayLink(void *, void *);
extern void func_00048360(void);
extern void FlushCollisionFinder(void *);
extern void ReleaseCharacterClassMotSyncAnim(void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);
extern void isysDeleteGroupAllObj(void *);
extern void FlushLayoutObjImmediate(unsigned char *);
extern void FlushJudgeVolumeObjImmediate(unsigned char *);

#define I(p, o) (*(int *)((char *)(p) + (o)))
#define P(p, o) (*(void **)((char *)(p) + (o)))

static inline char *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (char *)object + 0x90;
    case 0x16: return (char *)object + 0x90;
    default: return 0;
    }
}

static inline void resetTarget(unsigned char *object)
{
    char *chara = characterClass(object);
    char *other = characterClass(object);
    unsigned char *current = *(unsigned char **)(chara + 0x950);

    *(unsigned char **)(characterClass(current) + 0x960) = current;
    ChangeCharacterObjControlTarget(object, object);
    *(unsigned char **)(other + 0x960) = object;
}

void FlushCharacterObjImmediate(unsigned char *obj)
{
    char *c = characterClass(obj);
    unsigned char *t;
    char *w;
    int i;

    if (*(unsigned char **)(c + 0x950) != obj)
        resetTarget(obj);
    if (*(unsigned char **)(c + 0x960) != obj)
        resetTarget(*(unsigned char **)(c + 0x960));
    ResetCharacterClassPositionMemoryInfo(c);
    {
        char *l = c + 0xAC0;
        if (I(l, 0x4C) != 0) {
            I(l, 0x4C) = 0;
            DeleteTwoWayLink(l + 0x40);
        }
    }
    {
        int *m = (int *)(c + 0x2C8);
        if (m[1] != 0) {
            iosFree((void *)m[1]);
            m[0] = 0;
            m[1] = 0;
        }
    }
    if (I(c, 0xD00) != 0) {
        DeleteTwoWayLink(c + 0xD10);
        c[0xD90] = 0;
        I(c, 0xD00) = 0;
        c[0xD91] = 0;
    }
    DeleteAllTwoWayLink(c + 0xD04, func_00048360);
    FlushCollisionFinder(c + 0xE20);
    ReleaseCharacterClassMotSyncAnim(obj);
    w = characterClass(obj);
    for (i = 0; i < I(w, 0x3FC); i++) {
        char *g = (char *)(i * 0x80 + (int)P(w, 0x30C));
        void **node;
        void *last = 0;
        for (node = isysGroupForFirst(g, 0); node != 0; node = isysGroupForNext(node, 0)) {
            last = *node;
            isysRequestDeleteObj(last);
        }
        if (last != 0)
            isysGroupForExit(last, 0);
        isysDeleteGroupAllObj(g);
    }
    isysDeleteGroupAllObj(characterClass(obj) + 0x10E4);
    FlushLayoutObjImmediate(obj);
    FlushJudgeVolumeObjImmediate(obj);
}
