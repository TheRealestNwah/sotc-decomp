typedef int s128 __attribute__((mode(TI)));

extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(void *);
extern void SendCharaMotionSyncStartMsg(void *, void *);
extern void SCRSimpleExecCharaGeometry(void *);
extern void SetLayoutClassScaleElem(char *, float *, int);
extern void scrRun(void);

static inline void vecMulXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

void nico_parentAndScaleSync(void)
{
    void *thread;
    char *chara;
    char *layout;
    void *parent;
    s128 v[2];
    char *parentLayout;
    float *parentScale;

    thread = isysGetThisSubThread();
    chara = GetCharacterClass(thread);
    layout = GetLayoutClass(thread);
    parent = GetGeometryPointerObject(layout + 0xC0);
    if (parent != 0) {
        SendCharaMotionSyncStartMsg(thread, parent);
    }
    if (*(int *)(layout + 0x124) != 0) {
        SCRSimpleExecCharaGeometry(thread);
        SCRSimpleExecCharaGeometry(thread);
    } else {
        parent = 0;
    }
    v[0] = *(s128 *)(chara + 0x90);
    if (parent != 0) {
        layout = GetLayoutClass(thread);
        parentScale = (float *)(GetLayoutClass(parent) + 0x90);
        for (;;) {
            vecMulXYZ((float *)&v[1], (float *)&v[0], parentScale);
            SetLayoutClassScaleElem(layout, (float *)&v[1], 1);
            scrRun();
        }
    }
    for (;;) {
        scrRun();
    }
}
