extern int IsNonISysObjTypeRes(int);
extern void delete_object_animation_camera_region(void *);
extern void isysRequestDeleteObj(void *);
extern void FlushLayoutObj(void *);
extern void SubCallDeleteFuncNonISysObjTypeRes(void *, int);
extern void flushScriptObjImmediate(void *);
extern void FlushLayoutObjImmediate(void *);

typedef struct { int p0; int type; int p8; } SubRes;
typedef struct { char p0[0x30]; int count; char p34[0x20]; SubRes *res; } SubDef;
typedef struct { void *obj; void *res; char p8[0x48]; } SubObj;
typedef struct { int mot; int p4; int p8; } MotEntry;
typedef struct { char p0[0x1C0]; int motK; } CharClass;
typedef struct { char p0[0x10]; MotEntry *entries; } MotP;
typedef struct {
    char p0[0x11F8];
    SubDef *def;
    int p11FC;
    SubObj *subs;
} Work;
typedef struct {
    int p0;
    int p4;
    unsigned char type;
    char p9[0x17];
    Work work;
} Obj;

extern CharClass *GetCharacterClass(Obj *);
extern MotP *GetMotKToMotP(int);

static inline void deleteSubObjects(Obj *o)
{
    Work *w = (o->type ^ 0x16) == 0 ? (Work *)((char *)o + 0x20) : 0;
    SubObj *s = w->subs;
    SubRes *r = w->def->res;
    int i;

    for (i = 0; i < w->def->count; i++, s++, r++) {
        if (s->obj != 0) {
            if (!IsNonISysObjTypeRes(r->type) && r->p0 != 0 && r->type < 0x2B && r->type >= 0x27) {
                delete_object_animation_camera_region(s->obj);
            }
            isysRequestDeleteObj(s->obj);
            FlushLayoutObj(s->obj);
            s->obj = 0;
        }
    }
}

static inline void deleteNonISys(Obj *o)
{
    Work *w = o->type == 0x16 ? &o->work : 0;
    SubObj *s = w->subs;
    SubRes *r = w->def->res;
    MotEntry *m = GetMotKToMotP(GetCharacterClass(o)->motK)->entries;
    int i;

    for (i = 0; i < w->def->count; i++, s++, m++) {
        if (IsNonISysObjTypeRes((r++)->type)) {
            if (s->res != 0)
                SubCallDeleteFuncNonISysObjTypeRes(s->res, m->mot);
        }
    }
}

#ifdef NONMATCHING
/* 88 diffs: &o->work kept in a saved register across both loops */
static void func_000920F0(Obj *o)
{
    deleteNonISys(o);
    deleteSubObjects(o);
    flushScriptObjImmediate(o);
    FlushLayoutObjImmediate(o);
}
#endif
