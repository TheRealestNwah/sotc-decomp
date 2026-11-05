#ifdef NONMATCHING
/* 110 diffs: the vector math is scheduled differently and the stack layout differs */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { float f[4]; } __attribute__((aligned(8))) F4;
extern void get_world_matrixSR(void *, void *, void *, int);
extern float iosGetACosf(float);

/* Inverse of a rigid transform: transposed rotation, rotated negated translation. */
#define VU_INVERSE_MATRIX(dst, src) \
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n" \
                         "vsubw.x vf25, vf0, vf0w\n" \
                         "vmulx.xyz vf28, vf24, vf25x\n" \
                         "vsub.w vf28, vf28, vf28\n" \
                         "lq $8, 0x0(%1)\n" \
                         "lq $9, 0x10(%1)\n" \
                         "lq $10, 0x20(%1)\n" \
                         "qmfc2 $11, vf0\n" \
                         "pextlw $12, $9, $8\n" \
                         "pextuw $13, $9, $8\n" \
                         "pextlw $14, $11, $10\n" \
                         "pextuw $15, $11, $10\n" \
                         "pcpyld $8, $14, $12\n" \
                         "pcpyud $9, $12, $14\n" \
                         "pcpyld $10, $15, $13\n" \
                         "pcpyud $11, $13, $15\n" \
                         "qmtc2 $8, vf24\n" \
                         "qmtc2 $9, vf25\n" \
                         "qmtc2 $10, vf26\n" \
                         "vmulax.xyzw ACC, vf24, vf28x\n" \
                         "vmadday.xyzw ACC, vf25, vf28y\n" \
                         "vmaddaz.xyzw ACC, vf26, vf28z\n" \
                         "vmaddw.xyzw vf29, vf0, vf28w\n" \
                         "vsub.w vf29, vf29, vf29\n" \
                         "vadd.w vf29, vf29, vf0\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf29, 0x30(%0)\n" \
                         : : "r"(dst), "r"(src) \
                         : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory")

static inline void applyMatrix(void *out, void *m, void *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline void normalizeXYZ(void *out, void *a)
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
                         : : "r"(out), "r"(a) : "memory");
}

static inline void scaleXYZ(void *out, void *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline float dotXYZ(void *a, void *b)
{
    float dot;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static inline void crossXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_000C5FA0(char *e, void *a1, char *p)
{
    Vec4 dir;
    Vec4 cross;
    Vec4 m[4];

    if (*(int *)(p + 0x164) == 2) {
        F4 ref = { { -0.707106948f, 0.707106948f, 0.0f, 0.0f } };

        get_world_matrixSR(m, e + 0x30, a1, 1);
        VU_INVERSE_MATRIX(m, m);
        applyMatrix(&dir, m, e + 0x90);
        dir.f[2] = 0.0f;
        normalizeXYZ(&dir, &dir);
        scaleXYZ(&dir, &dir, -1.0f);
        *(float *)(e + 0x194) = iosGetACosf(dotXYZ(&ref, &dir));
        crossXYZ(&cross, &ref, &dir);
        if (cross.f[2] < 0.0f)
            *(float *)(e + 0x194) = 6.28318548f - *(float *)(e + 0x194);
    }
}
#endif
