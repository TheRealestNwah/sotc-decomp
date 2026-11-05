typedef struct {
    int count;
} ResList;

typedef struct {
    void *obj;
    void *pad;
} ResSlot;

typedef struct {
    unsigned int active : 4;
    unsigned int refs : 4;
} ResFlags;

typedef struct {
    char pad0[0x14];
    ResFlags flags;
} ResState;

typedef struct {
    char pad0[0x328];
    ResList *list;
    ResState *state;
    char pad330[0x338 - 0x330];
    ResSlot *slots;
    void *judge;
    char pad340[0x34C - 0x340];
    int bufSize;
    char pad350[4];
    void *buf;
} ResWork;

typedef struct {
    char pad0[8];
    unsigned char kind;
    char pad9[0x20 - 0x9];
    ResWork work;
} ResOwner;

extern void func_00087E40(ResOwner *);
extern void isysRequestDeleteObj(void *);
extern void FlushLayoutObj(void *);
extern void iosFree(void *);
extern void FlushJudgeVolumeClassImmediate(void *);
extern void FlushScriptLayoutObjImmediate(ResOwner *);
extern void FlushChildGroupManagerObj(ResOwner *);

static inline ResWork *getWork(ResOwner *owner)
{
    return owner->kind == 0xD ? &owner->work : 0;
}

static void func_00087F68(ResOwner *owner)
{
    ResWork *outer = getWork(owner);
    ResWork *work;
    ResList *list;
    int i;

    func_00087E40(owner);
    work = getWork(owner);
    list = work->list;
    for (i = 0; i < list->count; i++) {
        if (work->slots[i].obj != 0) {
            isysRequestDeleteObj(work->slots[i].obj);
            FlushLayoutObj(work->slots[i].obj);
        }
    }
    if (work->buf != 0) {
        iosFree(work->buf);
        work->buf = 0;
        work->bufSize = 0;
    }
    if (outer->judge != 0)
        FlushJudgeVolumeClassImmediate(outer->judge);
    FlushScriptLayoutObjImmediate(owner);
    FlushChildGroupManagerObj(owner);
    if (outer->state->flags.active)
        outer->state->flags.refs--;
}
