typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirect(void *, void *, void *, void *);
extern s128 *GetGeometryPointerSurfacePlane(void *);
extern void setAttainmentPosAndDir(void *, Vec4 *, Vec4 *);
extern int GetDebugDispType(void);
extern void glLoadIdentity(void);
extern void glColor4f(float, float, float, float);
extern void glDisable(int);
extern void glEnable(int);
extern void DebugDispRadiusIndicator(void *, float, int);

static inline void normalizeXYZ(float *output, const float *input)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(output), "r"(input) : "memory");
}
static inline void scaleXYZ(float *out, const float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}
static inline void addXYZ(float *out, const float *a, const float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void SCRFuncSetAttainForPreParallelTrans(void *obj, float d1, float d2)
{
    char *w = getSCRDataCtrlWork(obj);
    char *l = GetLayoutClass(obj);
    char buf[0x50];
    Vec4 n, pos, tgt, dir;

    if (ClipCollisionDirect(buf, *(void **)(l + 0x134), *(void **)(*(char **)(w + 0x407C) + 0x134), gcGlobalVar + 0x238)) {
        n.q = *GetGeometryPointerSurfacePlane(buf);
        n.f[1] = 0.0f;
        normalizeXYZ(n.f, n.f);
        scaleXYZ(tgt.f, n.f, -d1);
        addXYZ(tgt.f, tgt.f, *(float **)(GetLayoutClass(obj) + 0x134));
        tgt.f[3] = 1.0f;
        if (ClipCollisionDirect(buf, *(void **)(GetLayoutClass(obj) + 0x134), &tgt, gcGlobalVar + 0x238)) {
            scaleXYZ(pos.f, n.f, d2);
            addXYZ(pos.f, pos.f, (float *)(buf + 0x40));
            pos.f[3] = 1.0f;
            scaleXYZ(dir.f, n.f, -1.0f);
            dir.f[3] = 1.0f;
            setAttainmentPosAndDir(w, &pos, &dir);
            if (GetDebugDispType() == 3) {
                glLoadIdentity();
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                glDisable(1);
                DebugDispRadiusIndicator(&pos, 2.0f, 5);
                glEnable(1);
            }
        }
    }
}
