/* Parked attempt: 14 words differ from the Original. */
#ifdef NONMATCHING
/* 14 diffs: scheduling of two loop setups and f0/f1 numbering in the colour copy. */
typedef struct {
    float x, y, z, w;
} V4 __attribute__((aligned(8)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    unsigned int target;
    unsigned int cur;
    float timer;
    int pad;
    V4 col[5] __attribute__((aligned(16)));
} EyeWork;

typedef struct {
    unsigned int cond;
    unsigned int next;
    float time;
} EyeCond;

typedef struct {
    unsigned int tex;
    float x, y, z, w;
    float time;
} EyeCol;

extern int DldSysUndefSymbol;
extern int SCRConditionDef_ORIENT_FINISH;
typedef struct {
    char pad[0x190];
    float dt;
} GcGlobal;
extern GcGlobal gcGlobalVar;
extern char *getSCRDataCtrlWork(void *);
extern int execCondition(void *, void *);
extern void texScaleClut(int, V4 *);

static inline char *dldResolve(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline char *dldBase(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) : 0;
}


static inline void vecSub(V4 *out, V4 *a, V4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecScale(V4 *out, V4 *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(s) : "memory");
}

static inline void vecAdd(V4 *out, V4 *a, V4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void updateEyeWork(void *obj)
{
    EyeWork *e = (EyeWork *)(getSCRDataCtrlWork(obj) + 0x4100);
    EyeCond *c;
    EyeCol *l;
    EyeCol *k;
    V4 *dst;
    V4 *p;
    union {
        V4 v;
        u_long128 q;
    } col;
    V4 tmp;
    int clut;
    int i;

    if (e->cur != 0 && dldResolve(&((EyeCond *)e->cur)->next) != 0) {
        c = (EyeCond *)dldResolve(&((EyeCond *)e->cur)->next);
        while ((char *)SCRConditionDef_ORIENT_FINISH != dldResolve(&c->cond)) {
            if (c->time <= e->timer && execCondition(obj, c)) {
                e->target = (unsigned int)dldResolve(&c->next);
                break;
            }
            c++;
        }
    }
    if (e->cur != e->target) {
        if (e->cur == 0) {
            k = (EyeCol *)dldResolve((unsigned int *)e->target);
            if (k != 0) {
                for (p = e->col; dldBase(&k->tex) != 0;) {
                    tmp.x = k->x;
                    tmp.y = k->y;
                    tmp.z = k->z;
                    tmp.w = k->w;
                    k++;
                    col.v = tmp;
                    *(u_long128 *)p = col.q;
                    p++;
                }
            }
        }
        e->cur = e->target;
        e->timer = 0.0f;
    }
    if (e->cur != 0) {
        l = (EyeCol *)dldResolve((unsigned int *)e->cur);
        if (l != 0) {
            i = 0;
            dst = e->col;
            while (dldBase(&l->tex) != 0) {
                clut = *(int *)(dldBase(&l->tex) + 0xC);
                tmp.x = l->x;
                tmp.y = l->y;
                tmp.z = l->z;
                tmp.w = l->w;
                col.v = tmp;
                if (l->time > e->timer) {
                    vecSub(&tmp, &col.v, dst);
                    vecScale(&tmp, &tmp, gcGlobalVar.dt / (l->time - e->timer));
                    vecAdd(dst, dst, &tmp);
                } else {
                    *(u_long128 *)dst = col.q;
                }
                i++;
                texScaleClut(clut, dst++);
                l++;
                if (i >= 5)
                    return;
            }
        }
        e->timer += gcGlobalVar.dt;
    }
}
#endif
