typedef struct {
    char pad0[0xC0];
    char edge[0x124 - 0xC0];
    int f124;
    char pad128[0xF0 - 0xF0];
} Dummy;

extern void GetCollisionEdgePointerVertexPoint3(void *, void *);
extern float GetPlaneSlopeDegree(void *);
extern float *GetCollisionDBPlane(void *);
extern void CompletePlaneD(void *, void *);
extern float GetPointDistanceFromPlane(void *, void *);
extern float YUnitVector[];

void charrootdyn_getParentedEdgeInfo(char *obj, float *plane)
{
    int pts[3];
    float dir[4], cross1[4], cross2[4];
    int ok = 0;
    char *edge;
    int *p0, *p1;
    float deg, y, ang;
    float *pl;
    register int one __asm__("$2");

    *(int *)(obj + 0x610) = 0;
    if (*(int *)(obj + 0x124) != 0)
        ok = *(int *)(obj + 0xF0) == 4;
    if (ok) {
        edge = obj + 0xC0;
        GetCollisionEdgePointerVertexPoint3(pts, edge);
        p0 = (int *)pts[0];
        p1 = (int *)pts[1];
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             "lqc2 vf5, 0x0(%2)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             : : "r"(p1), "r"(p0), "r"(dir) : "memory");
        deg = GetPlaneSlopeDegree(dir);
        if (deg > 90.0f)
            ang = 90.0f - (180.0f - deg);
        else
            ang = 90.0f - deg;
        *(float *)(obj + 0x624) = ang;
        __asm__ __volatile__("" ::: "memory");
        one = 1;
        __asm__ __volatile__("" : "+r"(one));
        pl = plane;
        *(int *)(obj + 0x610) = one;
        if (pl == 0)
            pl = GetCollisionDBPlane(edge);
        y = pl[1];
        if (y < 0.0f ? y < -0.95f : y > 0.95f) {
            *(int *)(obj + 0x68C) = 0;
        } else if (*(float *)(obj + 0x624) > 85.0f) {
            *(int *)(obj + 0x68C) = 0;
        } else {
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vopmula.xyz ACC, vf5, vf6\n"
                                 "vopmsub.xyz vf7, vf6, vf5\n"
                                 "vsub.w vf7, vf7, vf7\n"
                                 "sqc2 vf7, 0x0(%2)\n"
                                 : : "r"(dir), "r"(YUnitVector), "r"(cross1) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vopmula.xyz ACC, vf5, vf6\n"
                                 "vopmsub.xyz vf7, vf6, vf5\n"
                                 "vsub.w vf7, vf7, vf7\n"
                                 "sqc2 vf7, 0x0(%2)\n"
                                 : : "r"(cross1), "r"(dir), "r"(cross2) : "memory");
            CompletePlaneD(cross2, p0);
            *(int *)(obj + 0x68C) = GetPointDistanceFromPlane(cross2, (void *)pts[2]) >= 0.0f ? -1 : 1;
        }
    }
}
