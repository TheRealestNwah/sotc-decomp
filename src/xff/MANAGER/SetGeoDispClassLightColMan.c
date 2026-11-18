typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *D_00136C00;
extern void ExecGlobalLightMan(void *, void *);
extern void SetWorkFromGlobalLight(void *);
extern void ExecGameLight(void *, int, void *);
extern void iosMakeLightColorMatrix(void *, void *, void *, void *, void *);
extern void iosMakeNormalLightMatrix(void *, void *, void *, void *, void *);
extern void GetDirColorFromWorkLight(void *, void *, void *);
static int func_0007ACD0(char *, char *, char *);

int SetGeoDispClassLightColMan(char *object)
{
    char *work = D_00136C00;
    unsigned char side = object[0xC0] & 1;
    if (*(int *)(object + 0xEC) != 0) {
        s128 position = ((Vec4 *)(object + 0x10))->q;
        *(float *)(work + 0x10) = 0.0f;
        ((Vec4 *)work)->q = position;
        *(float *)(work + 0x14) = *(float *)(work + 0x10);
        ((Vec4 *)work)->f[3] = 1.0f;
        *(int *)(work + 0x18) = side;
        *(int *)(work + 0x530) = 0;
        ExecGlobalLightMan(work, work);
        SetWorkFromGlobalLight(work);
        ExecGameLight(work, side, work);
        func_0007ACD0(work, object, work);
    }
    return 1;
}

static inline void scaleVec(void *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static int func_0007ACD0(char *w, char *obj, char *w2)
{
    Vec4 amb;
    Vec4 dir;
    char *l;
    int i;
    int idx = -1;
    char *dc = w + 0x80;
    char *col = w + 0x50;

    scaleVec(&amb, w + 0x340, 1.0f / 255.0f);
    amb.f[3] = 1.0f;
    i = 0;
    if (*(int *)(w2 + 0x18) != 0) {
        for (; i < 3; i++) {
            l = ((char **)(w + 0x534))[i];
            if (*(int *)(l + 0x30) & 4) {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            *(long *)(obj + 0xC0) &= ~2;
        } else {
            ((Vec4 *)(obj + 0x40))->q = ((Vec4 *)l)->q;
            *(float *)(obj + 0x4C) = *(float *)(l + 0x3C);
            scaleVec(col, l + 0x20, 1.0f / 255.0f);
            __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(col + 0x10) : "memory");
            __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(col + 0x20) : "memory");
            iosMakeLightColorMatrix(obj + 0x80, col, col + 0x10, col + 0x20, &amb);
            *(long *)(obj + 0xC0) |= 2;
        }
    } else {
        for (; i < 3; i++)
            GetDirColorFromWorkLight(dc + i * 16, col + i * 16, ((char **)(w + 0x534))[i]);
        *(int *)(dc + 0xC) = 0;
        *(int *)(dc + 0x1C) = 0;
        *(int *)(dc + 0x2C) = 0;
        dir.q = ((Vec4 *)(dc))->q;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(dir.f) : "memory");
        if (dir.f[1] > -0.70710677f)
            dir.f[1] = -0.70710677f;
        iosMakeNormalLightMatrix(obj + 0x40, dc, dc + 0x10, dc + 0x20, &dir);
        iosMakeLightColorMatrix(obj + 0x80, col, col + 0x10, col + 0x20, &amb);
    }
    return 1;
}
