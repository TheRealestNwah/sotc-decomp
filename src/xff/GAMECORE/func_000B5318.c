typedef union {
    char raw[0x34];
    struct {
        char pad0[0x30];
        int refCount;
    } s;
} AnimalType;

typedef struct {
    char pad0[0x10];
    AnimalType *types;
} AnimalTypeTable;

typedef struct {
    void *model;
    void *motion;
    int loaded;
    char padC[0x28];
    short type;
} SmallAnimal;

extern AnimalTypeTable SH_SmallAnimalTypeDEFAULT;
extern void unloadObj(void *);
extern char *func_000B7460(SmallAnimal *);
extern void stagemanager_unloadstageByStrptr_nowait_norefcount(char *);

static void func_000B5318(SmallAnimal *a)
{
    AnimalType *types;

    if (a->motion)
        unloadObj(a->motion);
    if (a->model)
        unloadObj(a->model);
    if (!a->loaded)
        return;
    types = SH_SmallAnimalTypeDEFAULT.types;
    types[a->type].s.refCount--;
    if (types[a->type].s.refCount != 0)
        return;
    stagemanager_unloadstageByStrptr_nowait_norefcount(func_000B7460(a));
}
