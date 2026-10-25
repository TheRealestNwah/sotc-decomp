typedef struct WeakPart {
    char pad0[0x28];
    long key;
    char pad30[0x28];
} WeakPart;

typedef struct Damage {
    int field0;
    float value;
} Damage;

extern char **GetSCRCharaAIWorkPtr(void *);

float getBossWeakCurDamage(void *object, long key)
{
    char *work;
    Damage *damage = 0;
    int i;

    work = *GetSCRCharaAIWorkPtr(object);
    for (i = 0; i < *(int *)(work + 0x54); i++) {
        if (key == (*(WeakPart **)(work + 0x10))[i].key) {
            damage = (Damage *)(*(char **)(work + 0xE8) + 0x24) + i;
            break;
        }
    }
    if (damage != 0) {
        return damage->value;
    }
    return 0.0f;
}
