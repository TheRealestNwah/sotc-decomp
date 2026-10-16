typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x184];
    float dt;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern s128 All1Vector;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void UpdateLayoutClassPastSimpleGeometry(void *);
extern void UpdateLayoutClassParentGeometry(void *, int, int);
extern void GetGeometryPointerScale(void *, void *);
extern void UpdateLayoutClassSimpleGeometry(void *, float);
extern void FlushCollisionWork(void *);
extern void scrRun(void);

void nico_optBoneParentScaleUpdateScript(void)
{
    void *th = isysGetThisSubThread();
    char *l = GetLayoutClass(th);

    for (;;) {
        UpdateLayoutClassPastSimpleGeometry(l);
        UpdateLayoutClassParentGeometry(l, 0, 0);
        __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                             "vmul.xyzw vf15, vf14, vf14\n"
                             "vaddy.x vf15, vf15, vf15y\n"
                             "vaddz.x vf15, vf15, vf15z\n"
                             "vaddw.x vf15, vf15, vf15w\n"
                             "vrsqrt Q, vf0w, vf15x\n"
                             "vwaitq\n"
                             "vmulq.xyzw vf15, vf14, Q\n"
                             "sqc2 vf15, 0x0(%0)\n"
                             : : "r"(*(void **)(l + 0x13C)) : "memory");
        if (*(int *)(l + 0x124) != 0)
            GetGeometryPointerScale(l + 0x90, l + 0xC0);
        else
            *(s128 *)(l + 0x90) = All1Vector;
        UpdateLayoutClassSimpleGeometry(l, gcGlobalVar.dt);
        FlushCollisionWork(th);
        scrRun();
    }
}
