/* Parked: 84 diffs, same size (157 words incl. the split tail func_0004A398; the earlier header's 95 was stale, the previous version scored 120). Ribbon per-frame update (caller func_00049198's sibling): when gcGlobalVar.f190 is nonzero, builds the direction from the layout position minus o+0x50 scaled by 1/(f190*speed) (VU0), runs func_00048008/00049350/00049FF8 and fills the per-point width/alpha array (0.1 up to the start index, 0.5 past the end index, linear blend between); then calls func_00049198, copies the point array, advances the timers and returns whether state == 7. VU0 runs match word for word; float constants must be written as 0.1f (gcc 2.96 truncates, 0x3DCCCCCC). Storing through a float/int union, the loop counter pinned to $4, o->iB held in a local, the tail through o+0x100 and an if-return each save diffs. Remaining: the Original schedules the f190*speed load after the first VU0 run, hoists g340 into a3 before the loop (skip path reuses it), advances p by 3 after the float constants, and stores pos before the f304/f1A4/f254 updates. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

typedef struct {
    char pad0[8];
    int owner;
    char padC[0x38 - 0xC];
    int state;
    int state2;
    float f40;
    char pad44[4];
    float f48;
    char pad4C[4];
    s128 pos;
    Vec dir;
    float *pts;
    float *prev;
    char pad78[0x84 - 0x78];
    int count;
    char pad88[0x94 - 0x88];
    float fA;
    int iB;
    float fC;
    char pad_a0[0x1A4 - 0xA0];
    float f1A4;
    char pad1A8[0x254 - 0x1A8];
    float f254;
    char pad258[0x304 - 0x258];
    float f304;
    char pad308[0x310 - 0x308];
    s128 q310;
    char pad320[0x320 - 0x320];
    s128 q320;
    char pad330[0x340 - 0x330];
    int g340;
    char pad344[0x350 - 0x344];
    float f350;
    float f354;
} Obj;

extern struct {
    char pad[0x190];
    float f190;
} gcGlobalVar;
extern char *GetLayoutClass(int);
extern void func_00048008(Obj *);
extern void func_00049350(Obj *, int);
extern void func_00049FF8(Obj *);
extern void func_00049198(Obj *, void *, int, int);
extern void *memcpy(void *, const void *, unsigned int);

typedef union { float f; int i; } FI;

static int func_0004A150(Obj *o)
{
    FI *p;
    register int i __asm__("$4");
    int t0;
    int end;
    int bi;
    float k;
    float inv;
    float f2;
    float t;
    int bits;
    float *lp;

    if (gcGlobalVar.f190 != 0.0f) {
        char *lay = GetLayoutClass(o->owner);

        lp = *(float **)(lay + 0x134);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "sqc2 vf7, 0x0(%2)\n"
                             :
                             : "r"(lp), "r"(&o->pos), "r"(&o->dir)
                             : "memory");
        k = gcGlobalVar.f190 * o->f350;
        if (0.0f < k) {
            inv = 1.0f / k;
            __asm__("mfc1 %0, %1" : "=r"(bits) : "f"(inv));
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "qmtc2.ni %1, vf6\n"
                                 "vmulx.xyzw vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 :
                                 : "r"(&o->dir), "r"(bits)
                                 : "memory");
        } else {
            __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(&o->dir) : "memory");
        }
        func_00048008(o);
        func_00049350(o, o->g340);
        func_00049FF8(o);
        p = (FI *)o->pts;
        bi = (int)o->fA;
        i = 0;
        t0 = bi + 1;
        if (!(t0 < o->count))
            t0 = bi;
        end = o->iB;
        p += 3;
        for (; i < o->count; i++) {
            if (i < t0) {
                p->f = 0.1f;
            } else if (i >= end) {
                p->f = 0.5f;
            } else {
                f2 = o->fA;
                t = ((float)i - f2) / (o->fC - f2);
                p->f = t * 0.5f + (1.0f - t) * 0.1f;
            }
            p += 4;
        }
    }
    func_00049198(o, o->pts, o->count, o->g340);
    if (gcGlobalVar.f190 == 0.0f)
        return 0;
    memcpy(o->prev, o->pts, o->count << 4);
    {
        float sp;

        o->state2 = o->state;
        sp = o->f350;
        o->f354 = sp;
        o->f48 = o->f48 + gcGlobalVar.f190 * sp;
        o->f40 = o->f40 + gcGlobalVar.f190 * sp;
    }
    o->pos = *(s128 *)*(float **)(GetLayoutClass(o->owner) + 0x134);
    {
        char *b = (char *)o + 0x100;
        float d = gcGlobalVar.f190 * o->f350;

        *(s128 *)(b + 0x210) = *(s128 *)(b + 0x220);
        *(float *)(b + 0x204) += d;
        *(float *)(b + 0xA4) += d;
        *(float *)(b + 0x154) += d;
    }
    if (o->state == 7)
        return 1;
    return 0;
}
#endif
