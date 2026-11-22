/* Steps a particle, handles its collision hit (reflect, absorb into the free list) and applies jitter. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

typedef union GWork {
    struct {
        char pad0[0xA8];
        union GWork *next;
    } s;
} GWork;

typedef struct GWorkList {
    int num;
    GWork *head;
    GWork *tail;
} GWorkList;

extern GWorkList B_001499B0;
extern float *D_001370D8;
extern float iosGetRandom(void);
extern void iosGetReflectVector(void *, void *, Vec4 *);
extern void func_000C66D8(void *, void *, void *, void *, void *, char *, char *);
extern int func_000C2360(Vec4 *, Vec4 *, char *, void *, void *, char *);
extern void func_000C68E0(char *, char *, char *, char *);

static inline void scaleXYZ(void *out, void *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline int particleGWorkRemove(GWorkList *list, GWork *work)
{
    GWork *prev;
    GWork *cur;
    GWork *head;

    head = list->head;
    if (head != 0) {
        cur = head;
        prev = 0;
        do {
            if (cur == work) {
                if (prev != 0) {
                    prev->s.next = work->s.next;
                }
                if (list->head == work) {
                    list->head = work->s.next;
                }
                if (list->tail == work) {
                    list->tail = prev;
                }
                list->num--;
                return 1;
            }
            prev = cur;
            cur = cur->s.next;
        } while (cur != 0);
    }
    return 0;
}

static inline void particleGWorkAppend(GWorkList *list, GWork *work)
{
    if (list->tail != 0) {
        list->tail->s.next = work;
    } else {
        list->head = work;
    }
    work->s.next = 0;
    list->tail = work;
    list->num++;
}

static int func_000C1FF0(char *w, char *e, char *y, char *cfg, char *p, void *ext, void *acc)
{
    if (*(int *)(cfg + 0x104) == 0) {
        func_000C66D8(w, acc, e, ext, y, cfg, p);
    } else {
        Vec4 old;
        Vec4 pos;
        Vec4 pl;
        int r;

        old.q = *(s128 *)w;
        func_000C66D8(w, acc, e, ext, y, cfg, p);
        if (*(int *)(w + 0xA4) == 0) {
            r = func_000C2360(&pos, &pl, e, &old, w, cfg);
            if (r == 1) {
                float f20, f21;
                *(int *)(w + 0xA4) = r;
                if (*(int *)(cfg + 0x16C) == r) {
                    ((Vec4 *)(w + 0x40))->i[0] = 0;
                    if (particleGWorkRemove((GWorkList *)(e + 0x124), (GWork *)w))
                        particleGWorkAppend(&B_001499B0, (GWork *)w);
                    return 1;
                }
                f20 = *(float *)(p + 0x11C);
                f21 = *(float *)(p + 0x120);
                ((Vec4 *)w)->q = pos.q;
                if (*(int *)(cfg + 0xC) == 2) {
                    if ((f20 < 0.0f) ? (-0.0001f < f20) : (f20 < 0.0001f)) {
                        if (0.0f <= f20)
                            f20 = 0.0001f;
                        else
                            f20 = -0.0001f;
                    }
                }
                iosGetReflectVector(w + 0x10, w + 0x10, &pl);
                scaleXYZ(w + 0x10, w + 0x10, f20);
                iosGetReflectVector(w + 0x20, w + 0x20, &pl);
                scaleXYZ(w + 0x20, w + 0x20, f21);
                if (*(int *)(cfg + 0xC) == 2) {
                    *(float *)(w + 0xA0) = *(float *)(w + 0x44);
                    ((Vec4 *)(w + 0x30))->q = ((Vec4 *)(w + 0x10))->q;
                }
            }
        }
    }
    if (*(int *)(cfg + 0x11C) != 0 && 0.0f < *D_001370D8) {
        float h = *(float *)(p + 0x118) * 0.5f;
        *(float *)(w + 0x0) += iosGetRandom() * *(float *)(p + 0x118) - h;
        *(float *)(w + 0x4) += iosGetRandom() * *(float *)(p + 0x118) - h;
        *(float *)(w + 0x8) += iosGetRandom() * *(float *)(p + 0x118) - h;
    }
    func_000C68E0(w, e, y, p);
    return 0;
}
