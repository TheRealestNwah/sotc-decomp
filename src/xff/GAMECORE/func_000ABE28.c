typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x70];
    Vec4 base;
    Vec4 a;
    Vec4 b;
    Vec4 c;
} KiteTgt;

typedef struct {
    char pad0[0x20];
    void *obj;
    void *first;
    void *found;
    int self;
    int hasFirst;
    KiteTgt *tgt;
    char pad38[0x40 - 0x38];
    char p40[0xC0];
    char p100[0x60];
    char p160[0x60];
    char p1C0[0x60];
    void *cur;
    char pad224[0x230 - 0x224];
    Vec4 dir;
    Vec4 flat;
    int mode;
    char pad254[0x258 - 0x254];
    int kind;
    char pad25C[0x2A0 - 0x25C];
    Vec4 quat;
    Vec4 iquat;
    char pad2C0[0x320 - 0x2C0];
    int sel;
} KiteWork;

typedef struct {
    char pad0[0x134];
    Vec4 *pos;
} Layout;

extern void *isysGetThisSubThread(void);
extern Layout *GetLayoutClass(void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern char *GetScriptCharacterClass(void *);
extern char *GetCharacterClass(void *);
extern void *SCRGetFirstObj(void *);
extern void AI_GetSmallAnimalAIParam(void *, Vec4 *, Vec4 *, Vec4 *, Vec4 *, Vec4 *);
extern char gcGlobalVar[];
extern Vec4 ZUnitVector;
extern int ControlMode_KITE_DEFAULT;
extern int ControlMode_KITE_TAKEOFF;
extern int ControlMode_KITE_FLY;
extern int ControlMode_KITE_SURFING;
extern int ControlMode_KITE_LANDING;
extern int ControlMode_MINOTOUR_KITE_SURFING;
extern int ControlMode_MINOTOUR_KITE_FLY;

static inline void quatRotateVector(Vec4 *out, Vec4 *quat0, Vec4 *vec0)
{
    register Vec4 *vec asm("$2") = vec0;
    register Vec4 *quat asm("$3") = quat0;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

static inline void normalizeXYZ(Vec4 *output, Vec4 *input)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
}

static inline void conjugate(Vec4 *out, Vec4 *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static void func_000ABE28(KiteWork *w)
{
    void *obj = 0;
    void *self = isysGetThisSubThread();
    Layout *myLayout = GetLayoutClass(w->obj);
    Layout *selfLayout = GetLayoutClass(self);
    void **it;
    int ctl;
    int mode;
    Vec4 tmp;

    w->found = 0;
    w->self = 1;
    for (it = isysGroupForFirst(gcGlobalVar + 0x2BC, 0); it != 0; it = isysGroupForNext(it, 0)) {
        int *p;
        obj = *it;
        p = *(int **)(GetScriptCharacterClass(obj) + 0x1200);
        if (p != 0 && *p == 0) {
            w->found = obj;
            break;
        }
    }
    if (obj != 0)
        isysGroupForExit(obj, 0);
    if (w->found != 0 && w->found != self)
        w->self = 0;

    w->first = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    if (w->first != 0)
        w->hasFirst = 1;
    else
        w->hasFirst = 0;

    ctl = *(int *)(GetCharacterClass(isysGetThisSubThread()) + 0x750);
    if (ctl == ControlMode_KITE_DEFAULT)
        mode = 0xD;
    else if (ctl == ControlMode_KITE_TAKEOFF)
        mode = 0xE;
    else if (ctl == ControlMode_KITE_FLY)
        mode = 0xF;
    else if (ctl == ControlMode_KITE_SURFING)
        mode = 0x10;
    else if (ctl == ControlMode_KITE_LANDING)
        mode = 0x11;
    else if (ctl == ControlMode_MINOTOUR_KITE_SURFING)
        mode = 0x10;
    else if (ctl == ControlMode_MINOTOUR_KITE_FLY)
        mode = 0xF;
    else
        mode = 0xD;
    w->mode = mode;

    quatRotateVector(&w->dir, &w->quat, &ZUnitVector);
    w->flat.q = w->dir.q;
    ((int *)&w->flat)[1] = 0;
    normalizeXYZ(&w->flat, &w->flat);
    conjugate(&w->iquat, &w->quat);

    AI_GetSmallAnimalAIParam(w->p40, myLayout->pos, selfLayout->pos, &w->iquat, &w->dir, &w->flat);
    if (w->hasFirst == 0) {
        w->cur = w->p40;
    } else {
        AI_GetSmallAnimalAIParam(w->p100, GetLayoutClass(w->first)->pos, selfLayout->pos, &w->iquat, &w->dir, &w->flat);
        w->cur = w->p100;
        if (w->kind == 5) {
            AI_GetSmallAnimalAIParam(w->p1C0, &w->tgt->base, selfLayout->pos, &w->iquat, &w->dir, &w->flat);
            w->cur = w->p1C0;
        } else if (w->kind == 6) {
            if (w->sel == 0)
                tmp.q = w->tgt->a.q;
            else if (w->sel == 1)
                tmp.q = w->tgt->b.q;
            else
                tmp.q = w->tgt->c.q;
            AI_GetSmallAnimalAIParam(w->p1C0, &tmp, selfLayout->pos, &w->iquat, &w->dir, &w->flat);
            w->cur = w->p1C0;
        }
    }
    if (w->self == 0)
        AI_GetSmallAnimalAIParam(w->p160, GetLayoutClass(w->found)->pos, selfLayout->pos, &w->iquat, &w->dir, &w->flat);
}
