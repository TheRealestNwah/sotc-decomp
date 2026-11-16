/* Parked: 12 diffs. Builds a stabilising quaternion from the collision edge at obj+0xC0 (type 4 only): copies the DB plane out if asked, then either aligns q to the edge direction crossed with Y (vertex points, VU0 cross product and normalise, GetQuaternionByAxisDirZY) or defers to func_00067068; with exchange set, q is multiplied by a half turn about Y. Remaining: s3/s4 hold obj and useEdge the other way round, and the argument moves before the func_00067068 call are ordered differently. The `pp` copy of pts came from a 25-minute permuter run. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern float YUnitVector[];
extern s128 *GetCollisionDBPlane(void *);
extern void GetCollisionEdgePointerVertexPoint(int *, void *);
extern void GetQuaternionByAxisDirZY(float *, float *, float *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);
extern void func_00067068(float *, s128 *, int, int, char *, int, int, int, float, float, float);

int charrootdyn_edgepointstab(float *q, s128 *plane, int a2, int a3, char *obj, int t1, int t2, int useEdge,
                              int exchange, int a9, float f0, float f1, float f2)
{
    float cross[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    int pts[2];
    int *pp;
    char *edge = obj + 0xC0;

    if (*(int *)(edge + 0x30) != 4)
        return 0;
    if (plane != 0)
        *plane = *GetCollisionDBPlane(edge);
    pp = pts;
    if (useEdge != 0) {
        GetCollisionEdgePointerVertexPoint(pp, edge);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             : : "r"(pts[1]), "r"(pts[0]), "r"(dir) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vopmula.xyz ACC, vf5, vf6\n"
                             "vopmsub.xyz vf7, vf6, vf5\n"
                             "vsub.w vf7, vf7, vf7\n"
                             "sqc2 vf7, 0x0(%2)\n"
                             : : "r"(dir), "r"(YUnitVector), "r"(cross) : "memory");
        __asm__ __volatile__(".set noreorder\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             ".set reorder\n"
                             : : "r"(cross), "r"(cross) : "memory");
        GetQuaternionByAxisDirZY(q, cross, YUnitVector);
    } else {
        func_00067068(q, plane, a2, a3, obj, t1, t2, a9, f0, f1, f2);
    }
    if (exchange != 0) {
        SetQuaternionByAxisRotateVWithNoRegularize(cross, -0x8000, YUnitVector);
        __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                             "lqc2 vf12, 0x0(%1)\n"
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
                             "sqc2 vf13, 0x0(%0)\n"
                             : : "r"(q), "r"(cross) : "memory");
    }
    return 1;
}
#endif
