/* Parked draft: probes a fan of eight directions (angles from RO_001813C8, rotated about Y) around
   a point against the path collision, keeps the hit nearest the point (squared distance via VU0
   w accumulate and the Q register read) and returns whether any hit was found. Written from the
   m2c draft; not yet compared closely. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern float RO_001813C8[8];
extern float RO_001813EC;
extern char pathJudgeFunc[];
extern int ClipCollisionDirectCallBackDoubleSide(void *, Vec4 *, Vec4 *, int, void *, int);
extern int getPathColiGroup(int);
extern void iosRotMatrixY(Vec4 *, float);

static inline void rotApply(Vec4 *out, Vec4 *m, Vec4 *v)
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

static inline void scaleXYZ(Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(*(int *)&s) : "memory");
}

static inline void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float distSq(Vec4 *a, Vec4 *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
    return r;
}

int getHitPosWayCollision(int path, Vec4 *out, Vec4 *center, float radius, float len)
{
    Vec4 rot[4] __attribute__((aligned(16)));
    Vec4 hit[4] __attribute__((aligned(16)));
    Vec4 dir __attribute__((aligned(16)));
    Vec4 probe __attribute__((aligned(16)));
    Vec4 end __attribute__((aligned(16)));
    float best = RO_001813EC;
    int i;

    out->q = center->q;
    for (i = 0; i < 8; i++) {
        float d;

        iosRotMatrixY(rot, RO_001813C8[i] * 0.017453292f);
        rotApply(&dir, rot, &probe);
        scaleXYZ(&dir, radius);
        addXYZ(&end, &dir, center);
        if (ClipCollisionDirectCallBackDoubleSide(hit, center, &end, getPathColiGroup(path), pathJudgeFunc, 0) != 0) {
            d = distSq(center, hit);
            if (d < best) {
                best = d;
                scaleXYZ(&dir, len);
                addXYZ(out, hit, &dir);
            }
        }
    }
    return best != RO_001813EC;
}
#endif
