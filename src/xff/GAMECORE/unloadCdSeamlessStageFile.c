typedef struct { unsigned int lo : 4; unsigned int hi : 28; } ChipFlags;
typedef struct { void *data[2]; ChipFlags flags[2]; char pad10[8]; } ChipRow;
typedef struct { char pad0[8]; ChipRow *chips; } StageMap;
extern StageMap D_0017A340;

static inline void *get_chip_object(int layer, int group)
{
    void *data = D_0017A340.chips[group].data[layer];
    return data != 0 ? *(void **)((char *)data + 0xC) : 0;
}

static inline int get_chip_state(int layer, int group)
{
    if (group != -1)
        return D_0017A340.chips[group].flags[layer].lo;
    return 7;
}

static inline void *get_chip_object_unless_loading(int layer, int group, unsigned int *count)
{
    void *object = get_chip_object(layer, group);
    if (get_chip_state(layer, group) == 5) {
        *count = 0;
        return 0;
    }
    *count = D_0017A340.chips[group].flags[layer].hi;
    return object;
}

extern void func_00024BA8(void);
typedef struct { char pad[0x308]; int stage; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern int createScriptObj(void (*)(void), void *, int, int, int, int, int, int);

void unloadCdSeamlessStageFile(int group, int layer)
{
    unsigned int count;
    void *obj = get_chip_object_unless_loading(layer, group, &count);

    if (obj != 0)
        createScriptObj(func_00024BA8, obj, gcGlobalVar.stage, 0x1000, 0, 1, 0, 0);
}
