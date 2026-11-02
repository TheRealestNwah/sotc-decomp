typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad[0x90];
    Vec4 scale;
} CharWork;

typedef struct {
    char pad[0x90];
    Vec4 scale;
    char padA0[0xC0 - 0xA0];
    char geo[0x124 - 0xC0];
    int parent;
} Layout;

extern void *isysGetThisSubThread(void);
extern CharWork *GetCharacterClass(void *);
extern Layout *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(void *);
extern void SendCharaMotionSyncStartMsg(void *, void *);
extern void SCRSimpleExecCharaGeometry(void *);
extern void SetLayoutClassScaleElem(Layout *, float *, int);
extern void scrRun(void);

static inline void vecMul(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

void nico_parentAndScaleSync(void)
{
    void *th = isysGetThisSubThread();
    CharWork *ch = GetCharacterClass(th);
    Layout *lay = GetLayoutClass(th);
    void *parent = GetGeometryPointerObject(lay->geo);
    Vec4 base;
    Vec4 s;

    if (parent != 0)
        SendCharaMotionSyncStartMsg(th, parent);
    if (lay->parent != 0) {
        SCRSimpleExecCharaGeometry(th);
        SCRSimpleExecCharaGeometry(th);
    } else
        parent = 0;
    base.q = ch->scale.q;
    if (parent != 0) {
        Layout *my = GetLayoutClass(th);
        Layout *pl = GetLayoutClass(parent);

        for (;;) {
            vecMul(s.f, base.f, pl->scale.f);
            SetLayoutClassScaleElem(my, s.f, 1);
            scrRun();
        }
    }
    for (;;)
        scrRun();
}
