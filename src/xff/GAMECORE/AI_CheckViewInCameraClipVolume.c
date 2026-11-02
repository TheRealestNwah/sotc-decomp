typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void *get_main_cameraman_camera_obj(void);
extern void *get_transform_matrix_set(void *obj);
extern float *get_WVC_matrix(void *set);

static inline void applyMatrix(Vec4 *out, float *m, Vec4 *v)
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

static inline void scaleVector(Vec4 *out, Vec4 *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

int AI_CheckViewInCameraClipVolume(Vec4 *out, Vec4 *pos)
{
    Vec4 v;
    float w;

    applyMatrix(&v, get_WVC_matrix(get_transform_matrix_set(get_main_cameraman_camera_obj())), pos);
    w = v.f[3];
    scaleVector(&v, &v, 1.0f / w);
    v.f[3] = w;
    out->q = v.q;
    if (v.f[0] >= -1.0f && v.f[0] <= 1.0f && v.f[1] >= -1.0f && v.f[1] <= 1.0f && w > 0.0f)
        return 1;
    return 0;
}
