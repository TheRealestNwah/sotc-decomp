typedef struct {
    char pad[0x2C];
    int layout;
    char pad30[0x4];
} AnimalType;

typedef struct {
    char pad[0x10];
    AnimalType *types;
} AnimalTypeTable;

typedef struct {
    char pad[0x20];
    char pos[0x10];
    float f30;
    short type;
    char pad36[0xA];
    float f40;
    char pad44[0xC];
    short s50;
    short s52;
} SObjNode;

extern AnimalTypeTable SH_SmallAnimalTypeDEFAULT;
extern void *isysGetThisSubThread(void);
extern SObjNode *getSObjNode(void *);
extern char *GetLayoutClass(void *);
extern void Kite_SetAnimalLayout(void *, void *, float, float, float);

typedef union { int i; short s; } IS;

static void func_0009E6C0(char *o)
{
    void *t = isysGetThisSubThread();
    SObjNode *n = getSObjNode(t);

    if (n != 0) {
        if (SH_SmallAnimalTypeDEFAULT.types != 0) {
            *(int *)(o + 0x274) = SH_SmallAnimalTypeDEFAULT.types[n->type].layout;
        }
        Kite_SetAnimalLayout(o + 0x380, n->pos, n->f30, n->f40, *(float *)(*(char **)(o + 0x20) + 0x14));
        ((IS *)(o + 0x8))->i = n->s52;
        *(int *)(o + 0x4) = n->s50;
    } else {
        char *l = GetLayoutClass(t);

        Kite_SetAnimalLayout(o + 0x380, *(void **)(l + 0x134), 10.0f, 3.0f, *(float *)(*(char **)(o + 0x20) + 0x14));
        *(int *)(o + 0x8) = 0;
        *(int *)(o + 0x4) = -1;
    }
}
