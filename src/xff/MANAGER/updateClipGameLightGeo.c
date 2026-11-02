extern int IsEnvelopeGameLightType(void *);
extern void UpdateClipGameLight(void *, char *);

static inline void mulQuaternion(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0(%1)\n"
                         "lqc2 vf12, 0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void applyMatrix(float *out, float *m, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

void updateClipGameLightGeo(char *obj, char *geo, void *light)
{
    if (light == 0)
        return;
    if (IsEnvelopeGameLightType(light) == 0 && *(int *)(obj + 0x124) == 0)
        return;
    {
        float *q = (float *)(geo + 0x20);
        mulQuaternion(q, *(float **)(obj + 0x13C), q);
    }
    {
        float *p = (float *)(geo + 0x10);
        applyMatrix(p, *(float **)(obj + 0x158), p);
    }
    UpdateClipGameLight(light, geo);
}
