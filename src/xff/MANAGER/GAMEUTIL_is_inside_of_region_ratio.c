/* Parked: 8 diffs, same size. Type 0 returns 1 - GAMEUTIL_get_dist_ratio(VU0 distance), types 1 and 3 build a matrix from quat+center and call GetRateInOutEllipticalSphereVolume / GetRateInOutCubeVolume with (x,y,z,1) inner/outer vectors, other types hit break 0. Writing the outer vector's w first puts the type 1 stores in the Original's order. Remaining: the Original schedules the type compare and pos copy before lui 1.0 in the type 1 path, and in the type 3 path stores cin.w (0x6C) before cout's x/y/z; all 56 placements of the two w stores leave that at 4. */
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
    Vec4 ein, eout, cin, cout;

    if (type == 0) {
        r = 1.0f - GAMEUTIL_get_dist_ratio(distance(pos, center), x0, x1);
    } else {
        register Vec4 *mp __asm__("$2") = m;
        __asm__("" : "+r"(mp));
        quatPosToMatrix(mp, quat, center);
        if (type == 1) {
            eout.f[3] = 1.0f;
            ein.f[0] = x0;
            ein.f[1] = y0;
            ein.f[2] = z0;
            ein.f[3] = 1.0f;
            eout.f[0] = x1;
            eout.f[1] = y1;
            eout.f[2] = z1;
            r = GetRateInOutEllipticalSphereVolume(m, pos, &ein, &eout);
        } else if (type == 2) {
            __asm__ __volatile__("break 0");
        } else if (type == 3) {
            cout.f[3] = 1.0f;
            cin.f[0] = x0;
            cin.f[1] = y0;
            cin.f[2] = z0;
            cin.f[3] = 1.0f;
            cout.f[0] = x1;
            cout.f[1] = y1;
            cout.f[2] = z1;
            r = GetRateInOutCubeVolume(m, pos, &cin, &cout);
        } else {
            __asm__ __volatile__("break 0");
        }
    }
    return r;
}
#endif
