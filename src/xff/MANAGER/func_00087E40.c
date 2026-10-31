typedef struct {
    int type;
    int pad4;
    signed char owned;
    char pad9[3];
} ResEntry;

typedef struct {
    int count;
    char pad4[0x18 - 0x4];
    ResEntry *entries;
} ResList;

typedef struct {
    void *region;
    void *obj;
} ResSlot;

typedef struct {
    char pad0[0x328];
    ResList *list;
    char pad32C[0x338 - 0x32C];
    ResSlot *slots;
} ResWork;

typedef struct {
    char pad0[8];
    unsigned char kind;
    char pad9[0x20 - 0x9];
    ResWork work;
} ResOwner;

extern int IsNonISysObjTypeRes(int);
extern void delete_object_animation_camera_region(void *);
extern void isysRequestDeleteObj(void *);
extern void SetGlobalLightAvailable(void *, int);
extern void SetGameLightAvailable(void *, int);

static void func_00087E40(ResOwner *owner)
{
    ResWork *work = owner->kind == 0xD ? &owner->work : 0;
    ResSlot *slot = work->slots;
    ResEntry *e = work->list->entries;
    int i;

    i = work->list->count;
    while (i-- != 0) {
        if (!IsNonISysObjTypeRes(e->type)) {
            if (e->owned != 0) {
                if (e->type < 0x2B) {
                    if (e->type >= 0x27)
                        delete_object_animation_camera_region(slot->region);
                }
                if (slot->obj != 0) {
                    isysRequestDeleteObj(slot->obj);
                    slot->obj = 0;
                }
            }
        } else {
            switch (e->type) {
            case 0x18:
                if (slot->obj != 0)
                    SetGlobalLightAvailable(slot->obj, 0);
                break;
            case 0x1B:
            case 0x1C:
            case 0x21:
            case 0x22:
            case 0x23:
                if (slot->obj != 0)
                    SetGameLightAvailable(slot->obj, 0);
                break;
            }
        }
        e++;
        slot++;
    }
}
