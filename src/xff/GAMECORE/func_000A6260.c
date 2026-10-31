typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0xE4];
    float pathWidth;
    float pathHeight;
    char padEC[0x118 - 0xEC];
    float reach;
} KiteParam;

typedef struct {
    char pad0[0x20];
    KiteParam *param;
    char pad24[0x40 - 0x24];
    int busy;
    char pad44[0x260 - 0x44];
    int event;
    char pad264[0x26C - 0x264];
    int mode;
    int state;
    int next;
    char pad278[0x290 - 0x278];
    float time;
    char pad294[0x590 - 0x294];
    char path[0x600 - 0x590];
    Vec4 pos;
    int eventArg;
    char pad614[0x620 - 0x614];
    Vec4 target;
    char pad630[0x6A0 - 0x630];
    char check[0x740 - 0x6A0];
    float limit;
    char pad744[0x7D8 - 0x744];
    int done;
} Kite;

extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern int Kite_CmpPathPoint(void *, void *);
extern void Kite_StartEventCheck(void *, int);
extern void Kite_EndEventCheck(void *);
extern int AI_CheckPathPoint(void *, void *, float, float);
extern int func_0009F830(Kite *);
extern int func_0009FB88(Kite *);

static inline void endCheck(Kite *k)
{
    k->next = 9;
    Kite_EndEventCheck(k->check);
}

static inline int timeUp(Kite *k)
{
    if (k->time >= k->limit && k->mode == 15)
        return 1;
    return 0;
}

static inline int inReach(Kite *k)
{
    char *lay = GetLayoutClass(isysGetThisSubThread());
    float r = k->param->reach + 10.0f;
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "vmul.xyz vf7, vf7, vf7
"
                         "vaddy.x vf7, vf7, vf7y
"
                         "vaddz.x vf7, vf7, vf7z
"
                         "qmfc2.ni $2, vf7
"
                         "mtc1 $2, %0
"
                         : "=f"(d) : "r"(*(float **)(lay + 0x134)), "r"(&k->pos) : "$2");
    return d < r * r;
}

static void func_000A6260(Kite *k)
{
    if (k->state != k->next)
        return;
    switch (k->state) {
    case 1:
        if (func_0009F830(k))
            endCheck(k);
        break;
    case 0:
    case 10:
        if (!Kite_CmpPathPoint(&k->pos, &k->target))
            endCheck(k);
        break;
    case 2:
    case 4:
    case 6:
        if (k->event == 0x1C) {
            k->next = 8;
            Kite_StartEventCheck(k->check, k->eventArg);
        }
        break;
    case 3:
    case 5:
        if (timeUp(k))
            endCheck(k);
        break;
    case 7:
        if (k->done)
            endCheck(k);
        break;
    case 11:
        if (inReach(k))
            endCheck(k);
        break;
    case 8:
        if (func_0009FB88(k))
            endCheck(k);
        break;
    case 12:
    case 13:
        if (k->busy == 0)
            endCheck(k);
        break;
    case 14:
        if (AI_CheckPathPoint(isysGetThisSubThread(), k->path, k->param->pathHeight, k->param->pathWidth))
            endCheck(k);
        break;
    }
}
