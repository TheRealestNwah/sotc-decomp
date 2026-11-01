typedef int s128 __attribute__((mode(TI)));
typedef struct {
    char pad0[0x184];
    float scale;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern s128 All1Vector;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern void UpdateLayoutClassParentGeometry(char *, int, int);
extern void UpdateLayoutClassSimpleGeometry(char *, float);
extern void GetGeometryPointerScale(void *, void *);
extern void FlushCollisionWork(void *);
extern void scrRun(void);

#define VU_QUAT_NORMALIZE(q) \
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n" \
                         "vmul.xyzw vf15, vf14, vf14\n" \
                         "vaddy.x vf15, vf15, vf15y\n" \
                         "vaddz.x vf15, vf15, vf15z\n" \
                         "vaddw.x vf15, vf15, vf15w\n" \
                         "vrsqrt Q, vf0w, vf15x\n" \
                         "vwaitq\n" \
                         "vmulq.xyzw vf15, vf14, Q\n" \
                         "sqc2 vf15, 0x0(%0)\n" \
                         : : "r"(q) : "memory")

void nico_optBoneParentScaleUpdateScript(void)
{
    void *th = isysGetThisSubThread();
    char *c = GetLayoutClass(th);
    s128 *one = &All1Vector;
    GlobalVar *g = &gcGlobalVar;

    for (;;) {
        UpdateLayoutClassPastSimpleGeometry(c);
        UpdateLayoutClassParentGeometry(c, 0, 0);
        {
            register float *rq __asm__("$3") = *(float **)(c + 0x13C);
            VU_QUAT_NORMALIZE(rq);
        }
        if (*(int *)(c + 0x124) != 0) {
            GetGeometryPointerScale(c + 0x90, c + 0xC0);
        } else {
            *(s128 *)(c + 0x90) = *one;
        }
        UpdateLayoutClassSimpleGeometry(c, g->scale);
        FlushCollisionWork(th);
        scrRun();
    }
}
