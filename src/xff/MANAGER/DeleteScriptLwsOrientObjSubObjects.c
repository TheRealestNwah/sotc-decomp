extern int IsNonISysObjTypeRes(int);
extern void delete_object_animation_camera_region(void *);
extern void isysRequestDeleteObj(void *);
extern void FlushLayoutObj(void *);

typedef struct { int p0; int type; int p8; } SubRes;
typedef struct { char p0[0x30]; int count; char p34[0x20]; SubRes *res; } SubDef;
typedef struct { void *obj; char p4[0x4C]; } SubObj;
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

void DeleteScriptLwsOrientObjSubObjects(Obj *o)
{
    Work *w = o->type == 0x16 ? &o->work : 0;
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
