typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

extern Vec4 YUnitVector;
extern Vec4 ZeroPoint;
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
extern void *memset(void *, int, unsigned int);
extern void iosRotMatrixY(float *, float);
extern void iosRotMatrixAxis(float *, float, float *, int);
extern void iosApplyRotMatrix(float *, float *, float *);
extern void iosTransposeMatrix(float *, float *);
extern void create_original_view_matrix(float *, float *, float *, float *);

static inline void vecCross(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

int CAM_get_new_look_at_posi_from_camera_posi_and_rotXY(float *out, int flag, float *dir, float *pos, float *eye,
                                                         float rotX, float rotY, float len)
{
    Vec4 m[4];
    Vec4 axis;
    Vec4 ofs;
    Vec4 v;
    int nx = !GAMEUTIL_is_nearly_equal_zero(rotX, 0.0001f);
    int ny = !GAMEUTIL_is_nearly_equal_zero(rotY, 0.0001f);

    if (nx == 1 || ny == 1 || flag == 0) {
        memset(v, 0, 16);
        v[2] = 1.0f;
        if (ny) {
            iosRotMatrixY(m[0], rotY);
            iosApplyRotMatrix(v, m[0], v);
        }
        if (nx) {
            vecCross(axis, YUnitVector, v);
            iosRotMatrixAxis(m[0], rotX, axis, 0);
            iosApplyRotMatrix(v, m[0], v);
        }
        create_original_view_matrix(m[0], ZeroPoint, eye, YUnitVector);
        iosTransposeMatrix(m[0], m[0]);
        iosApplyRotMatrix(v, m[0], v);
        vecScale(ofs, v, len);
        vecAdd(out, pos, ofs);
        return 1;
    }
    *(u_long128 *)out = *(u_long128 *)dir;
    return 0;
}
