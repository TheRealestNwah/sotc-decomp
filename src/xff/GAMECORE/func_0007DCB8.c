/* Parked: 9 diffs, same size. Edge hit test for a collision surface: for each of the three neighbouring surfaces that is present, not of attribute class 0xA800 and faces up, builds the vertical plane through that edge (cross with YUnitVector), and if the start point lies in front of it and the segment crosses it, checks the crossing point against the two triangles of the edge quad with a VU0 barycentric run (one asm block with div.s and the stores, like the Original macro); on a hit it stores the crossing point and the plane normal. Remaining: register allocation swaps the d-vector pointer (a1 in the Original) with the s/t out pointer (v1). Permuter: 20 min at -j2, nothing below baseline. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef float Vec[4] __attribute__((aligned(16)));

extern int GetCollisionDBNext3Direct(void *out, void *surface);
extern unsigned long *GetCollisionDBAttributeAdr(void *surface);
extern float *GetCollisionDBPlane(void *surface);
extern void GetCollisionDBEdgeVertexPoint(void *out, void *surface, int index);
extern void CompletePlaneD(void *plane, void *point);
extern float GetPointDistanceFromPlane(void *plane, void *point);
extern int GetPlaneCrossPos(void *out, void *plane, void *a, void *b);
extern void GetNormalPlane(void *out, void *plane);
extern float YUnitVector[];
extern float RO_0017E260[];

static inline void vsub(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(out) : "memory");
}

static inline void vadd(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(out) : "memory");
}

static inline void vcross(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(out) : "memory");
}

static inline void bary(void *a, void *b, void *p, float *ps, float *pt)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "lqc2 vf6, 0x0(%1)
"
                         "lqc2 vf7, 0x0(%2)
"
                         "vopmula.xyz ACC, vf5, vf6
"
                         "vopmsub.xyz vf8, vf6, vf5
"
                         "vsub.w vf8, vf8, vf8
"
                         "vopmula.xyz ACC, vf8, vf6
"
                         "vopmsub.xyz vf9, vf6, vf8
"
                         "vsub.w vf9, vf9, vf9
"
                         "vaddw.x vf10, vf0, vf0w
"
                         "vmul.xyz vf11, vf9, vf7
"
                         "vaddax.x ACC, vf0, vf11x
"
                         "vmadday.x ACC, vf10, vf11y
"
                         "vmaddz.x vf10, vf10, vf11z
"
                         "qmfc2.ni $2, vf10
"
                         "mtc1 $2, $f2
"
                         "vaddw.x vf10, vf0, vf0w
"
                         "vmul.xyz vf11, vf9, vf5
"
                         "vaddax.x ACC, vf0, vf11x
"
                         "vmadday.x ACC, vf10, vf11y
"
                         "vmaddz.x vf10, vf10, vf11z
"
                         "qmfc2.ni $2, vf10
"
                         "mtc1 $2, $f3
"
                         "div.s $f0, $f2, $f3
"
                         "vopmula.xyz ACC, vf8, vf5
"
                         "vopmsub.xyz vf9, vf5, vf8
"
                         "vsub.w vf9, vf9, vf9
"
                         "vaddw.x vf10, vf0, vf0w
"
                         "vmul.xyz vf11, vf9, vf7
"
                         "vaddax.x ACC, vf0, vf11x
"
                         "vmadday.x ACC, vf10, vf11y
"
                         "vmaddz.x vf10, vf10, vf11z
"
                         "qmfc2.ni $2, vf10
"
                         "mtc1 $2, $f2
"
                         "vaddw.x vf10, vf0, vf0w
"
                         "vmul.xyz vf11, vf9, vf6
"
                         "vaddax.x ACC, vf0, vf11x
"
                         "vmadday.x ACC, vf10, vf11y
"
                         "vmaddz.x vf10, vf10, vf11z
"
                         "qmfc2.ni $2, vf10
"
                         "mtc1 $2, $f3
"
                         "div.s $f1, $f2, $f3
"
                         "swc1 $f0, 0x0(%3)
"
                         "swc1 $f1, 0x0(%4)
"
                         : : "r"(a), "r"(b), "r"(p), "r"(ps), "r"(pt) : "$2", "$f0", "$f1", "$f2", "$f3", "memory");
}

static inline int ok(float *s, float *t)
{
    float m = -0.00002f;
    return *s > m && *t > m && *s + *t - 1.0f < 0.00002f;
}

static inline int hitEdge(void *surface, int index, s128 *out, void *normal, void *a, void *b)
{
    s128 *vp[2];
    Vec v0;
    Vec e;
    Vec e2;
    Vec plane;
    Vec cross;
    Vec d;
    float s, t;
    int r;

    GetCollisionDBEdgeVertexPoint(vp, surface, index);
    *(s128 *)v0 = *vp[0];
    vsub(e, vp[1], v0);
    vcross(plane, e, YUnitVector);
    vadd(e2, e, RO_0017E260);
    CompletePlaneD(plane, v0);
    if (GetPointDistanceFromPlane(plane, a) > 0.0f) {
        if (GetPlaneCrossPos(cross, plane, a, b)) {
            vsub(d, cross, v0);
            bary(e, e2, d, &s, &t);
            r = ok(&s, &t);
            if (!r) {
                bary(e2, RO_0017E260, d, &s, &t);
                r = ok(&s, &t);
            }
            if (r) {
                *out = *(s128 *)cross;
                if (normal)
                    GetNormalPlane(normal, plane);
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

static int func_0007DCB8(s128 *out, void *normal, void *a, void *b, void *surface)
{
    int next[6];
    int *item = next;
    int i;

    if (GetCollisionDBNext3Direct(next, surface)) {
        for (i = 0; i < 3; i++, item += 2) {
            if (item[0] == 0)
                continue;
            if ((*GetCollisionDBAttributeAdr(item) & (0xF800UL << 20)) == (0xA800UL << 20))
                continue;
            if (!(GetCollisionDBPlane(item)[1] >= 0.0f))
                continue;
            if (hitEdge(surface, i, out, normal, a, b))
                return 1;
        }
    }
    return 0;
}
#endif
