typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *iosgluGetCameraContext(void);
extern void iosScaleMatrix(void *, float, float, float);
extern char *GetLayoutClass(void *);
extern void modelDisp(void *, void *);
extern void iosDlLockObj(void *);
extern void shadowDisp(void *, void *, void *, void *, int, void *, float, void *);

static inline void mtxMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "lqc2 vf24, 0x0(%2)\n"
                         "lqc2 vf25, 0x10(%2)\n"
                         "lqc2 vf26, 0x20(%2)\n"
                         "lqc2 vf27, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf27, 0x30(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static void func_00078778(void *unused, char *o, char *p)
{
    char *layout = *(char **)(o + 0x194);
    char *m;
    char *x;
    Vec4 *src;
    Vec4 *cam;
    int i;
    int n;

    if (layout == 0) {
        Vec4 sm[4];
        char *v;
        char *c;
        float scale;

        n = *(short *)(o + 0x1B4);
        cam = (Vec4 *)(iosgluGetCameraContext() + 0x1A0);
        src = *(Vec4 **)(o + 0x15C);
        for (i = 0; i < n; i++) {
            mtxMul(&(*(Vec4 **)(*(char **)(*(char **)(o + 0x144) + 0xC) + 0x104))[i * 4 + ((i + 1) >> 6)], cam, src);
            src += 4;
        }
        v = *(char **)(*(char **)(**(char ***)(o + 0x144) + 0x20) + 8);
        if (v != 0 && *(int *)(v + 0x3C) != 0 && (c = iosgluGetCameraContext()) != 0)
            scale = 1.0f / (*(float *)(c + 0xC) / 500.0f);
        else
            scale = 1.0f;
        if (scale != 1.0f) {
            int n2 = *(short *)(o + 0x1B4);
            iosScaleMatrix(sm, scale, scale, scale);
            i = 0;
            if (i < n2) {
            loop:
                {
                mtxMul(&(*(Vec4 **)(*(char **)(*(char **)(o + 0x144) + 0xC) + 0x104))[i * 4 + ((i + 1) >> 6)], &(*(Vec4 **)(*(char **)(*(char **)(o + 0x144) + 0xC) + 0x104))[i * 4 + ((i + 1) >> 6)], sm);
                }
                i++;
                if (i >= n2)
                    goto out;
                goto loop;
            }
        out:;
        }
    } else {
        *(char **)(*(char **)(o + 0x144) + 0xC) = *(char **)(*(char **)(GetLayoutClass(layout) + 0x144) + 0xC);
    }
    m = *(char **)(o + 0x144);
    if (!(*(unsigned long long *)(m + 0x260) & 0x20))
        modelDisp(m, *(void **)(o + 0x15C));
    if (*(void **)(o + 0x194) == 0) {
        x = *(char **)(*(char **)(o + 0x144) + 0x280);
        if (x != 0) {
            iosDlLockObj(x);
            m = *(char **)(o + 0x144);
            if (!(*(unsigned long long *)(m + 0x260) & 0x40)) {
                void *s = *(void **)(*(char **)(m + 0x280) + 0x20);
                shadowDisp(*(void **)(m + 0xC), s, *(void **)(o + 0x134),
                           s ? *(void **)(o + 0x160) : *(void **)(o + 0x15C),
                           *(short *)(o + 0x1B4), 0, 0.0f, 0);
            }
        }
    }
}
