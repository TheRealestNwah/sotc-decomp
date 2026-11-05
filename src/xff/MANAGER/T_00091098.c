typedef struct {
    int type;
    int pad[2];
} Entry;

typedef struct {
    int count;
    char pad4[0x14];
    Entry *entries;
} List;

typedef struct {
    void *pad;
    void *obj;
} Slot;

typedef struct {
    char pad0[0x328];
    List *list;
    char pad32C[0x338 - 0x32C];
    Slot *slots;
} Work;

typedef struct {
    char pad0[8];
    unsigned char kind;
    char pad9[0x20 - 9];
    Work work;
} Owner;

extern void func_00087F68(Owner *);
extern void DeleteCollMan(void *);
extern void DeleteGlobalLight(void *);
extern void DeleteGameLight(void *);

static inline Work *getWork(Owner *owner)
{
    return owner->kind == 0xD ? &owner->work : 0;
}

static void T_00091098(Owner *owner)
{
    Work *work;
    Slot *slot;
    Entry *e;
    int n;

    func_00087F68(owner);
    work = getWork(owner);
    slot = work->slots;
    e = work->list->entries;
    n = work->list->count;
    while (n-- != 0) {
        if (slot->obj != 0) {
            switch (e->type) {
            case 15:
            case 16:
                break;
            case 17:
                DeleteCollMan(slot->obj);
                break;
            case 24:
                DeleteGlobalLight(slot->obj);
                break;
            case 27:
            case 28:
            case 33:
            case 34:
            case 35:
                DeleteGameLight(slot->obj);
                break;
            }
            slot->obj = 0;
        }
        e++;
        slot++;
    }
}
