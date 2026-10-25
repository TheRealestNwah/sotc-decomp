extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern int execCondition(void *, unsigned int *);

typedef struct BossTrigger {
    char pad0[0x28];
    long key;
    char pad30[0x24];
    unsigned int condition;
} BossTrigger;

typedef struct BossTex {
    char pad0[0x10];
    BossTrigger *entries;
    char pad14[0x40];
    int count;
} BossTex;

typedef struct AIWork {
    BossTex *tex;
} AIWork;

extern AIWork *GetSCRCharaAIWorkPtr(void *);

int chkBossTrigTurnOff(int trigger)
{
    void *boss = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    long key = ((long)trigger + 0x1B) << 31;
    BossTex *work;
    int i;

    if (boss == 0) {
        return 0;
    }
    work = GetSCRCharaAIWorkPtr(boss)->tex;
    for (i = 0; i < work->count; i++) {
        if (key == work->entries[i].key) {
            return execCondition(boss, &work->entries[i].condition);
        }
    }
    return 1;
}
