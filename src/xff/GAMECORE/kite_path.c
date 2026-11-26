/* Kite path work: the path points the small animals (kites) fly between,
 * picked at random inside their area, plus the leader/child path checks. */
#include "common.h"
#include "gamecore/kite_path.h"

typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

typedef union {
    s128 q;
    float f[4];
} Vec4Q;

/* Kite_InitKitePathWork */

typedef struct {
    char pad[0x14];
    int id;
    char pad18[0x1C];
} AnimalType;

typedef struct {
    char pad[0x10];
    AnimalType *types;
} AnimalTypeTable;

typedef struct {
    char pad[0x34];
    short type;
} SObjNode;

/* Kite_GetPassageWork. The point position is copied through an IntOrQuad
 * union so gcc keeps it ahead of the area store. */

typedef union {
    int i;
    u_long128 q;
} IntOrQuad;

typedef struct {
    int t[45];
} Tbl;

extern AnimalTypeTable SH_SmallAnimalTypeDEFAULT;
extern SObjNode *getSObjNode(void *);
extern void *memset(void *, int, unsigned int);
extern float iosGetRandom(void);
extern float AI_GetInterRatio(float, float, float, float, float);
extern char *getPassageWork(void *, int);
extern char *getPointDataByAreaIdx(void *, int, int);
extern void AI_InitAnimalLayout(void *);
extern char *GetLayoutClass(void *);
extern void updateUserPathWork(void *, void *);
extern void *isysGetThisSubThread(void);


static inline void initPoint(KitePathPoint *p)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(p) : "memory");
    p->a = -1;
    p->b = 0;
    p->c = -1;
}

static inline void vecAddXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecSubXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float vecDist(float *a, float *b)
{
    float d;

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
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline float vecLength(float *v)
{
    float d;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(v) : "$2", "memory");
    return d;
}

static inline void vecNormalize(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecUnit(float *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v) : "memory");
}

static inline int samePt(PassPt *a, PassPt *b)
{
    if (a->idx == b->idx && a->area == b->area)
        return 1;
    return 0;
}

static inline float distanceSquareXZ(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline int checkPathPoint(void *obj, float *pos, float r, float h)
{
    float r2 = r * r;
    char *c = GetLayoutClass(obj);
    float *p;
    float half;
    float d;

    if (c == 0)
        return 0;
    half = h * 0.5f;
    p = *(float **)(c + 0x134);
    if (p[1] < pos[1] - half)
        return 0;
    if (pos[1] + half < p[1])
        return 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(p), "r"(pos) : "$2");
    if (r2 < d)
        return 0;
    return 1;
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void Kite_InitKitePathWork(KitePathWork *w, void *obj, float x, float y)
{
    SObjNode *n = getSObjNode(obj);
    KiteSub *s;
    int i;

    w->b = -1;
    w->a = -1;
    if (n != 0 && SH_SmallAnimalTypeDEFAULT.types != 0)
        w->b = SH_SmallAnimalTypeDEFAULT.types[n->type].id;
    initPoint(&w->pts[0]);
    initPoint(&w->pts[1]);
    initPoint(&w->pts[2]);
    initPoint(&w->pts[3]);
    initPoint(&w->pts[4]);
    initPoint(&w->pts[5]);
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&w->pos) : "memory");
    w->x = x;
    w->y = y;
    w->e8 = 0;
    w->ec = 0;
    w->obj = obj;
    s = &w->sub;
    s->obj = obj;
    initPoint(&s->pts[0]);
    initPoint(&s->pts[1]);
    initPoint(&s->pts[2]);
    initPoint(&s->pts[3]);
    s->count = 4;
    s->x = x;
    s->y = y;
    s->s98 = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&s->pos) : "memory");
    for (i = 9; i >= 0; i--)
        s->list[i] = 0;
    Kite_InitSpecialPathWork(w->special);
}

static void func_000ACDF0(char *pt, float *area, char *kite)
{
    VecQ off;
    VecQ save;
    Vec4 a;
    Vec4 b;
    union {
        Tbl s;
        struct {
            Vec4 np;
            VecQ o;
        } c;
    } u;
    float step = area[4] * 0.70710677f * 2.0f / 3.0f;
    int prev = *(int *)(kite + 0x1E4);
    int sel;

    save.q = *(u_long128 *)pt;
    memset(a, 0, 0x10);
    a[3] = 1.0f;
    memset(b, 0, 0x10);
    b[3] = 1.0f;
    u.s = (Tbl){{2, 2, 2, 2, 7, 3, 3, 3, 3, 6, 8, 8, 8, 8, 3, 7, 7, 7, 7, 8, 1, 3, 5,
                 7, 7, 1, 1, 1, 1, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 2, 6, 6, 6, 6, 1}};
    sel = u.s.t[prev * 5 + (int)(iosGetRandom() * 4.99)];
    a[0] = iosGetRandom() * step * 0.5f;
    a[2] = iosGetRandom() * step * 0.5f;
    if (sel % 3 == 0)
        b[0] = -step * 1.5f;
    else if ((sel - 1) % 3 == 0)
        b[0] = -step * 0.5f;
    else
        b[0] = step * 0.5f;
    if (sel < 3)
        b[2] = -step * 1.5f;
    else if (sel < 6)
        b[2] = -step * 0.5f;
    else
        b[2] = step * 0.5f;
    vecAddXYZ(off.f, a, b);
    *(int *)(kite + 0x1E4) = sel;
    off.f[1] = (iosGetRandom() - 0.5f) * area[5] * 2.0f;
    {
        float dy;
        float d;

        vecAddXYZ(u.c.np, area, off.f);
        u.c.o.q = save.q;
        dy = u.c.o.f[1] - u.c.np[1];
        if (dy < 0.0f)
            dy = -dy;
        u.c.np[1] = 0.0f;
        u.c.o.f[1] = 0.0f;
        d = vecDist(u.c.o.f, u.c.np);
        if (d < dy) {
            if (off.f[1] < 0.0f)
                d = -d;
            off.f[1] = d;
        }
    }
    vecAddXYZ((float *)pt, area, off.f);
    if (++*(int *)(pt + 0x10) > 0xFFFFFF)
        *(int *)(pt + 0x10) = 100;
    *(int *)(pt + 0x14) = *(int *)(kite + 0x1BC + (int)((iosGetRandom() - 0.0001f) * 10.0f) * 4);
}

void KiteSpecial_SetNewPathPoint(float *pt, int unused, char *kite, float *target)
{
    KiteArea *area = (KiteArea *)(kite + 0x100);
    Vec4 d;
    Vec4 dir;
    Vec4 ofs;
    float dy;
    float h;

    func_000ACDF0((char *)pt, (float *)(kite + 0x1F0), kite);
    vecSubXYZ(d, pt, area->center);
    dy = d[1];
    d[1] = 0;
    ((VecQ *)dir)->q = ((VecQ *)d)->q;
    {
        float len = vecLength(d);
        float r = area->radius;

        if (r < len) {
            float lim;
            float t;

            lim = (d[1] < r - 50.0f) ? r - 50.0f : r * 0.5f;
            t = AI_GetInterRatio(iosGetRandom(), 0.0f, 1.0f, lim, r);
            vecNormalize(dir);
            vecScale(ofs, dir, t);
            pt[0] = area->center[0] + ofs[0];
            pt[2] = area->center[2] + ofs[2];
        }
    }
    h = -area->height;
    if (dy < h) {
        ofs[1] = h;
        pt[1] = area->center[1] + ofs[1];
    }
    if (30.0f < vecDist(target, pt)) {
        vecSubXYZ(ofs, pt, target);
        vecNormalize(ofs);
        vecScale(ofs, ofs, 30.0f);
        vecAddXYZ(pt, target, ofs);
    }
}

static PathPt *func_000AD410(Kite *k, int which)
{
    PathWork *pw = &k->pw;
    PathPt *p;

    if (which == 0) {
        pw->saveCur = pw->cur;
        if (pw->cur.idx == -1) {
            pw->cur.idx = 99;
            if (k->kind == 8)
                KiteSpecial_SetNewPathPoint((float *)&pw->cur, (int)k->special, (char *)k, (float *)k->area);
            else
                func_000ACDF0((char *)&pw->cur, (float *)k->area, (char *)k);
        } else if (pw->flag != 0 && pw->next.idx != -1) {
            if (k->kind == 8)
                KiteSpecial_SetNewPathPoint((float *)&pw->cur, (int)k->special, (char *)k, (float *)&pw->saveCur);
            else
                pw->cur = pw->next;
        }
        return &pw->cur;
    }
    if (which == 1) {
        pw->saveNext = pw->next;
        if (pw->next.idx != -1) {
            p = &k->pw.next;
            if (pw->flag != 0)
                goto call;
            goto out;
        }
        pw->next.idx = 100;
    call:
        p = &pw->next;
        if (k->kind == 8)
            KiteSpecial_SetNewPathPoint((float *)p, (int)k->special, (char *)k, (float *)&pw->saveNext);
        else
            func_000ACDF0((char *)p, (float *)k->area, (char *)k);
    out:
        return p;
    }
    return 0;
}

int Kite_GetPassageWork(int unused, void *owner, int *kite, PassWork *w, int flag)
{
    char *pw0 = 0;
    char *pw1 = 0;
    PassPt a;
    PassPt b;
    char *p;
    char *q;
    PassPt *v;

    if (owner) {
        pw0 = getPassageWork(owner, 0);
        pw1 = getPassageWork(owner, 1);
    }
    vecUnit(a.pos);
    a.area = -1;
    a.pt = 0;
    a.idx = -1;
    vecUnit(b.pos);
    b.area = -1;
    b.pt = 0;
    b.idx = -1;
    if (pw0 && w->x4 >= 0) {
        p = getPointDataByAreaIdx(owner, *(short *)(pw0 + 0x14), *(int *)(pw0 + 0x1C));
        if (!p)
            return 0;
        ((IntOrQuad *)a.pos)->q = *(u_long128 *)p;
        a.area = *(short *)(pw0 + 0x14);
        a.idx = *(int *)(pw0 + 0x1C);
        if (*kite == 6)
            a.pt = 0;
        else
            a.pt = *(short *)(p + 0x1C);
    } else {
        if (*kite == 6)
            return 0;
        if (flag)
            v = (PassPt *)func_000AD410((Kite *)kite, 0);
        else
            v = (PassPt *)(kite + 0x48);
        if (v)
            a = *v;
    }
    if (pw1 && w->x4 >= 0) {
        q = getPointDataByAreaIdx(owner, *(short *)(pw1 + 0x14), *(int *)(pw1 + 0x1C));
        if (!q)
            return 0;
        ((IntOrQuad *)b.pos)->q = *(u_long128 *)q;
        b.area = *(short *)(pw1 + 0x14);
        b.idx = *(int *)(pw1 + 0x1C);
        if (*kite == 6)
            b.pt = 0;
        else
            b.pt = *(short *)(q + 0x1C);
    } else {
        if (flag)
            v = (PassPt *)func_000AD410((Kite *)kite, 1);
        else
            v = (PassPt *)(kite + 0x50);
        if (v)
            b = *v;
    }
    if (w->prev.p[0].area == -1)
        w->prev.p[0] = a;
    if (w->prev.p[1].area == -1)
        w->prev.p[1] = b;
    if (w->cur.p[0].area == -1)
        w->cur.p[0] = a;
    if (w->cur.p[1].area == -1)
        w->cur.p[1] = b;
    if (!flag) {
        if (!samePt(&a, &w->prev.p[0])) {
            if (samePt(&a, &w->cur.p[0]))
                w->cur.p[1] = b;
        }
        if (*(int *)((char *)w + 0xE8)) {
            if (samePt(&a, &w->cur.p[0])) {
                w->cur.p[0] = b;
            } else if (samePt(&w->cur.p[1], &a)) {
                if (!samePt(&w->cur.p[0], &w->cur.p[1])) {
                    w->cur.p[0] = a;
                    w->cur.p[1] = b;
                }
            }
        }
        if (samePt(&w->cur.p[0], &a) || samePt(&w->cur.p[0], &b) || samePt(&w->cur.p[1], &a))
            goto done;
        if (w->save.p[0].area != -1 && w->save.p[1].area != -1) {
            w->cur = w->save;
            goto done;
        }
    }
    w->cur.p[0] = a;
    w->cur.p[1] = b;
done:
    w->prev.p[0] = a;
    w->prev.p[1] = b;
    *(int *)((char *)w + 0xE8) = 0;
    *(int *)((char *)w + 0x1B8) = 0;
    return 0;
}

void Kite_InitSpecialPathWork(void *layout)
{
    AI_InitAnimalLayout(layout);
}

int AI_CheckPathPoint(void *obj, float *pos, float r, float h)
{
    float r2 = r * r;
    char *c = GetLayoutClass(obj);
    float *p;
    float half;
    float d;

    if (c == 0)
        return 0;
    half = h * 0.5f;
    p = *(float **)(c + 0x134);
    if (p[1] < pos[1] - half)
        return 0;
    if (pos[1] + half < p[1])
        return 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(p), "r"(pos) : "$2");
    if (r2 < d)
        return 0;
    return 1;
}

int Kite_CmpPathPoint(char *a, char *b)
{
    if (*(int *)(a + 0x18) != *(int *)(b + 0x18)) {
        goto no;
    }
    if (*(int *)(a + 0x10) != *(int *)(b + 0x10)) {
        goto no;
    }
    return 1;
no:
    return 0;
}

void Kite_InitKitePathPoint(KitePathPoint *p)
{
    initPoint(p);
}

void AI_UpdateLeaderPathWork(void *path, char *w)
{
    char *pw = w + 0x120;
    float pos[4] __attribute__((aligned(16)));

    if (path != 0 && *(int *)(w + 4) >= 0) {
        updateUserPathWork(*(void **)(w + 0xF0), path);
        return;
    }
    vecAddXYZ(pos, (float *)pw, (float *)(w + 0x1A0));
    *(int *)(pw + 0x98) = checkPathPoint(*(void **)(pw + 0xC8), pos, *(float *)(pw + 0x90), *(float *)(pw + 0x94));
}

void AI_UpdateChildPathWork(char *work)
{
    void *obj = *(void **)(work + 0xF0);
    char *layout;
    float *point;
    float radius, height, r2, half;
    Vec4Q pos;

    isysGetThisSubThread();
    layout = GetLayoutClass(obj);
    radius = *(float *)(work + 0xE0);
    height = *(float *)(work + 0xE4);
    r2 = radius * radius;
    pos.q = *(s128 *)(work + 0x10);
    vecAdd(pos.f, pos.f, (float *)(work + 0xD0));
    *(int *)(work + 0xE8) = 0;
    *(int *)(work + 0xEC) = 0;
    half = height * 0.5f;
    point = (float *)*(int *)(layout + 0x134);
    if (point[1] < pos.f[1] - half)
        return;
    if (pos.f[1] + half < point[1])
        return;
    if (r2 < distanceSquareXZ(point, pos.f))
        return;
    *(int *)(work + 0xE8) = 1;
    *(int *)(work + 0xEC) = 1;
}

void Kite_InitKiteAdvertisePathWork(void *arg0)
{
    ((void (*)())Kite_InitKitePathWork)();
    (*(int *)((char *)(arg0) + 4)) = 0;
}
