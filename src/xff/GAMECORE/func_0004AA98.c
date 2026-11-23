typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef struct Seg {
    char pad0[0x370];
    s128 f370;
    struct Seg *f380;
    int f384;
} Seg;

typedef struct {
    char pad0[0x20];
    union { float f; int i; } uv[4];
    char pad30[0x30 - 0x30];
} Vtx;

typedef struct {
    char pad0[0x14];
    int f14;
    int f18;
    int f1C;
    char pad20[0x30 - 0x20];
    Vec4 f30;
    int f40;
    float *f44;
    Vtx *f48;
    int f4C;
    char pad50[0x54 - 0x50];
    Seg *f54;
    int f58;
} Ctl;

typedef struct {
    int f0;
} ScrObj;

extern int D_0017A9B0;
extern char rootPtn[];
extern int isysGetThisSubThread(void);
extern float AI_GetInterRatio(float, float, float, float, float);
extern ScrObj *createScriptObj(void *, int, void *, int, int, int, int, int);
extern void *iosMallocAlign(int, int, int);
extern void setScriptObjArgument(ScrObj *, void *);
extern void SetScriptObjDeleteCallBackFunc(ScrObj *, void *, void *);
extern void scrRunM(int);
extern unsigned int iosGetMallocRootPtnRemainSize(void);
extern void GAMEUTIL_set_custom_boss_interest_position(void *);
extern void func_0004A760(Seg *, int, Ctl *, int);
extern void func_0004B048(void);
extern void func_0004AFD8(void);

static inline void vadd3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vscale4(void *out, void *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(s) : "memory");
}

static void func_0004AA98(Ctl *c)
{
    int thr;
    int i;
    int j;
    int n;
    int k;
    int done = 0;
    float *p;
    float lim;
    float cnt;
    float one;
    Seg *s;
    Seg *t;
    Seg *q;
    ScrObj *obj;
    int size;
    int sum;

    thr = isysGetThisSubThread();
    D_0017A9B0 = 0;
    one = 1.0f;
    n = c->f14;
    p = c->f44;
    lim = (float)n - (float)n * 0.1f;
    for (i = 0; i < n; i++, p++) {
        if ((float)i < lim)
            *p = one;
        else
            *p = AI_GetInterRatio((float)i, lim, (float)(n - 1), 1.0f, 0.0f);
    }
    if (c->f1C > 0) {
        Vtx *v = c->f48;
        int m;
        for (j = 0; j < 2; j++) {
            for (m = 0; m < c->f14; m++) {
                if (m == 0) {
                    v[m].uv[j * 2].f = (float)j;
                    v[m].uv[j * 2 + 1].i = 0;
                } else {
                    v[m].uv[j * 2].f = (float)j;
                    v[m].uv[j * 2 + 1].f = 1.0f - (float)(m % 2) * 0.5f;
                }
            }
        }
    }
    k = 0;
    while (k < c->f40) {
        n = c->f14 * 32 + 0x429;
        size = n;
        if (k >= c->f1C)
            size += c->f4C;
        if (k >= 3 && iosGetMallocRootPtnRemainSize() <= 0xFFFFF)
            break;
        obj = createScriptObj(func_0004B048, 0, rootPtn, 0x2000, size, 8, thr, 0);
        if (obj == 0)
            break;
        t = c->f54;
        s = iosMallocAlign(obj->f0, 0x390, 0x10);
        s->f380 = 0;
        if (t == 0) {
            c->f54 = s;
        } else {
            while (t->f380)
                t = t->f380;
            t->f380 = s;
        }
        func_0004A760(s, obj->f0, c, k);
        setScriptObjArgument(obj, s);
        SetScriptObjDeleteCallBackFunc(obj, func_0004AFD8, s);
        scrRunM(1);
        k++;
    }
    c->f18 = k;
    c->f58 = 1;
    if (k == 0) {
        D_0017A9B0 = 1;
        for (;;)
            scrRunM(1);
    }
    cnt = (float)k;
    for (;;) {
        q = c->f54;
        sum = 0;
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&c->f30) : "memory");
        for (; q; q = q->f380) {
            sum += q->f384;
            vadd3(&c->f30, &c->f30, &q->f370);
        }
        vscale4(&c->f30, &c->f30, 1.0f / cnt);
        c->f30.f[3] = 1.0f;
        GAMEUTIL_set_custom_boss_interest_position(&c->f30);
        if (sum > 0 && !done) {
            D_0017A9B0 = 1;
            done = 1;
        }
        scrRunM(1);
    }
}
