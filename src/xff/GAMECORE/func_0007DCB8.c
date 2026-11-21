/* Edge hit test for a collision surface: for each of the three neighbouring surfaces that is present, not of attribute class 0xA800 and faces up, builds the vertical plane through that edge (cross with YUnitVector), and if the start point lies in front of it and the segment crosses it, checks the crossing point against the two triangles of the edge quad with a VU0 barycentric run (one asm block with div.s and the stores, like the Original macro); on a hit it stores the crossing point and the plane normal. The register variables keep the d-vector pointer in $a1 and the s out pointer in $v1 across both barycentric runs, as in the Original. */
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

#define VSUB(out, a, b) \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n" \
                         "lqc2 vf6, 0x0(%1)\n" \
                         "vsub.xyz vf5, vf5, vf6\n" \
                         "sqc2 vf5, 0x0(%2)\n" \
                         : : "r"(a), "r"(b), "r"(out) : "memory")

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

/* A macro, not an inline function: the register variables at the call site must reach the asm operands directly. */
#define BARY(a, b, p, ps, pt) \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n" \
                         "lqc2 vf6, 0x0(%1)\n" \
                         "lqc2 vf7, 0x0(%2)\n" \
                         "vopmula.xyz ACC, vf5, vf6\n" \
                         "vopmsub.xyz vf8, vf6, vf5\n" \
                         "vsub.w vf8, vf8, vf8\n" \
                         "vopmula.xyz ACC, vf8, vf6\n" \
                         "vopmsub.xyz vf9, vf6, vf8\n" \
                         "vsub.w vf9, vf9, vf9\n" \
                         "vaddw.x vf10, vf0, vf0w\n" \
                         "vmul.xyz vf11, vf9, vf7\n" \
                         "vaddax.x ACC, vf0, vf11x\n" \
                         "vmadday.x ACC, vf10, vf11y\n" \
                         "vmaddz.x vf10, vf10, vf11z\n" \
                         "qmfc2.ni $2, vf10\n" \
                         "mtc1 $2, $f2\n" \
                         "vaddw.x vf10, vf0, vf0w\n" \
                         "vmul.xyz vf11, vf9, vf5\n" \
                         "vaddax.x ACC, vf0, vf11x\n" \
                         "vmadday.x ACC, vf10, vf11y\n" \
                         "vmaddz.x vf10, vf10, vf11z\n" \
                         "qmfc2.ni $2, vf10\n" \
                         "mtc1 $2, $f3\n" \
                         "div.s $f0, $f2, $f3\n" \
                         "vopmula.xyz ACC, vf8, vf5\n" \
                         "vopmsub.xyz vf9, vf5, vf8\n" \
                         "vsub.w vf9, vf9, vf9\n" \
                         "vaddw.x vf10, vf0, vf0w\n" \
                         "vmul.xyz vf11, vf9, vf7\n" \
                         "vaddax.x ACC, vf0, vf11x\n" \
                         "vmadday.x ACC, vf10, vf11y\n" \
                         "vmaddz.x vf10, vf10, vf11z\n" \
                         "qmfc2.ni $2, vf10\n" \
                         "mtc1 $2, $f2\n" \
                         "vaddw.x vf10, vf0, vf0w\n" \
                         "vmul.xyz vf11, vf9, vf6\n" \
                         "vaddax.x ACC, vf0, vf11x\n" \
                         "vmadday.x ACC, vf10, vf11y\n" \
                         "vmaddz.x vf10, vf10, vf11z\n" \
                         "qmfc2.ni $2, vf10\n" \
                         "mtc1 $2, $f3\n" \
                         "div.s $f1, $f2, $f3\n" \
                         "swc1 $f0, 0x0(%3)\n" \
                         "swc1 $f1, 0x0(%4)\n" \
                         : : "r"(a), "r"(b), "r"(p), "r"(ps), "r"(pt) : "$2", "$f0", "$f1", "$f2", "$f3", "memory")

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
            {
                register void *dp __asm__("$5") = d;
                register float *ps __asm__("$3");
                {
                    register void *cp __asm__("$3") = cross;
                    VSUB(dp, cp, v0);
                }
                ps = &s;
                BARY(e, e2, dp, ps, &t);
                r = ok(&s, &t);
                if (!r) {
                    BARY(e2, RO_0017E260, dp, ps, &t);
                    r = ok(&s, &t);
                }
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
