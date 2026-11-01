typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; int i[4]; } V;
typedef struct { void *obj; unsigned int id; } CollisionRef;
typedef struct { char p0[0x54]; int *res; char p58[0x38]; } SubDef;
typedef struct { char p0[0x8]; SubDef *defs; } Geo;
typedef struct { char p0[0x20]; Geo *geo; } Model;
typedef struct {
    char p0[0x154];
    s128 *quat;
    int p158;
    int mats;
    char p160[0x24];
    Model *model;
} LayoutClass;
extern LayoutClass *GetLayoutClass(void *);
extern s128 *func_0009E2D8(s128 *, LayoutClass *, int);

void GetCollisionDBOriginQuatPos(V *out, CollisionRef *ref)
{
    unsigned int id = ref->id;
    int node = (id >> 24) & 0x7F;
    int idx = id & 0xFFFFFF;
    LayoutClass *c = GetLayoutClass(ref->obj);

    if ((int)ref->id < 0) {
        out[0].q = c->quat[node];
        out[1].q = *(s128 *)(c->mats + node * 64 + 0x30);
    } else {
        out[1].q = *func_0009E2D8(&out->q, c, c->model->geo->defs[node].res[idx]);
    }
}
