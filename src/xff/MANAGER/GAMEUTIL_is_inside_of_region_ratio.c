/* Parked: 4 diffs, same size. Type 0 returns 1 - GAMEUTIL_get_dist_ratio(VU0 distance), types 1 and 3 build a matrix from quat+center and call GetRateInOutEllipticalSphereVolume / GetRateInOutCubeVolume with (x,y,z,1) inner/outer vectors, other types hit break 0. Block-local aggregate initializers for the inner/outer vectors put the type 3 path in the Original's order. Remaining: in the type 1 path the Original schedules the type compare constant and the pos copy before lui 1.0; eout-first, a shared 1.0 local and a pos copy local leave that at 4 or worse. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GetRateInOutEllipticalSphereVolume(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
extern float GetRateInOutCubeVolume(Vec4 *, Vec4 *, Vec4 *, Vec4 *);

static inline float distance(Vec4 *a, Vec4 *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void quatPosToMatrix(Vec4 *m, Vec4 *qp, Vec4 *pos)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(m), "r"(pos), "r"(qp));
}

float GAMEUTIL_is_inside_of_region_ratio(int type, Vec4 *pos, Vec4 *center, Vec4 *quat,
                                         float x0, float y0, float z0, float x1, float y1, float z1)
{
    float r = 0.0f;
    Vec4 m[4];

    if (type == 0) {
        r = 1.0f - GAMEUTIL_get_dist_ratio(distance(pos, center), x0, x1);
    } else {
        register Vec4 *mp __asm__("$2") = m;
        __asm__("" : "+r"(mp));
        quatPosToMatrix(mp, quat, center);
        if (type == 1) {
            Vec4 ein = {.f = {x0, y0, z0, 1.0f}};
            Vec4 eout = {.f = {x1, y1, z1, 1.0f}};
            r = GetRateInOutEllipticalSphereVolume(m, pos, &ein, &eout);
        } else if (type == 2) {
            __asm__ __volatile__("break 0");
        } else if (type == 3) {
            Vec4 cin = {.f = {x0, y0, z0, 1.0f}};
            Vec4 cout = {.f = {x1, y1, z1, 1.0f}};
            r = GetRateInOutCubeVolume(m, pos, &cin, &cout);
        } else {
            __asm__ __volatile__("break 0");
        }
    }
    return r;
}
#endif
