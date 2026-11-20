typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef union {
    struct { int a, b, c, d; } i;
    float f[4];
} PercRes;

typedef struct {
    char pad0[0x18];
    float lost;
    float h;
    float v;
    float bow;
} PercParam;

typedef struct {
    Vec4 pos;
    Vec4 last;
    float hTime;
    float vTime;
    float lostTime;
    int lost;
    PercRes res;
    PercParam *param;
    int unk44;
    void *target;
    char *targetLay;
    float distXZ;
    float dist;
    float bowTime;
} PercWork;

extern struct { char pad[0x190]; float dt; } gcGlobalVar;
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void perceptionExec(void *, PercWork *, PercRes *, void *);
extern int equipmentInvisibilityCloak(void);
extern int getSoundBowPos(PercWork *, void *);

static inline float distXZ(void *a, void *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2", "memory");
    return d;
}

static inline float distXYZ(void *a, void *b)
{
    float len;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(a), "r"(b) : "$2", "memory");
    return len;
}

#define DT (gcGlobalVar.dt)

/* PercRes and the target layout's position pointer share unions with floats so
 * their loads stay after the preceding float stores, as in the Original. */
union PU { Vec4 *p; float f; };
void updatePerceptionWork(void *obj)
{
    PercRes res;
    PercWork *w;
    PercParam *p;
    char *lay;
    char *t;

    w = (PercWork *)(getSCRDataCtrlWork(obj) + 0x4030);
    p = w->param;
    lay = GetLayoutClass(obj);
    t = w->targetLay;
    w->distXZ = distXZ(*(void **)(t + 0x134), *(void **)(lay + 0x134));
    w->dist = distXYZ(*(void **)(t + 0x134), *(void **)(lay + 0x134));
    if (w->param == 0) {
        w->lost = 0;
        return;
    }
    perceptionExec(obj, w, &res, *(void **)(t + 0x134));
    w->res = res;
    if (equipmentInvisibilityCloak() != 0) {
        w->lostTime = w->lostTime <= 0.0f ? 0.0f : w->lostTime;
    } else {
        if (w->hTime < -p->h)
            w->hTime = -p->h;
        if (w->vTime < -p->v)
            w->vTime = -p->v;
        if (w->lostTime < -p->lost)
            w->lostTime = -p->lost;
    }
    if (res.i.a == 0 && res.i.b == 0) {
        if (getSoundBowPos(w, *(void **)(lay + 0x134))) {
            w->bowTime = p->bow;
            w->lostTime = 0.0f <= w->lostTime ? 0.0f : w->lostTime;
        } else {
            w->bowTime -= DT;
            w->bowTime = w->bowTime <= 0.0f ? 0.0f : w->bowTime;
            if (w->bowTime <= 0.0f)
                w->pos.q = w->last.q;
        }
        w->lostTime += DT;
        if (0.0f < w->lostTime) {
            w->hTime = -p->h;
            w->vTime = -p->v;
        }
    } else {
        if (res.i.a)
            w->hTime += DT;
        if (res.i.b)
            w->vTime += DT;
        if (0.0f < w->hTime || 0.0f < w->vTime) {
            w->lostTime = -p->lost;
            w->pos.q = ((union PU *)(w->targetLay + 0x134))->p->q;
            w->last.q = ((union PU *)(w->targetLay + 0x134))->p->q;
            if (w->vTime <= 0.0f)
                w->vTime = 0.0f;
            else if (w->hTime <= 0.0f)
                w->hTime = 0.0f;
        }
    }
    if (w->lostTime <= 0.0f) {
        w->bowTime = 0.0f;
        w->lost = 1;
    } else {
        w->lost = 0;
    }
}
