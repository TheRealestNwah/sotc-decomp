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

static inline void releaseGroup(void *group)
{
    void *object = 0;
    void **entry;

    for (entry = isysGroupForFirst(group, 0); entry != 0;
         entry = isysGroupForNext(entry, 0)) {
        object = *entry;
        isysRequestDeleteObj(object);
    }
    if (object != 0)
        isysGroupForExit(object, 0);
    isysDeleteGroupAllObj(group);
}

void ReleaseCharacterClassMotSyncAnim(unsigned char *object)
{
    releaseGroup(characterClass(object) + 0xD92);
    releaseGroup(characterClass(object) + 0xD96);
}

void ReleaseCharacterClassAddMotSyncAnimAll(unsigned char *object)
{
    char *character = characterClass(object);
    int i;

    for (i = 0; i < *(int *)(character + 0x3FC); i++)
        releaseGroup(*(char **)(character + 0x30C) + i * 0x80);
}
