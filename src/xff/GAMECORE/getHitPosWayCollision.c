/* Parked: 15 words off. Probes a fan of eight directions (angles from RO_001813C8 in degrees,
   rotated about Y from ZDirVector) of length radius around center against the path collision,
   keeps the hit nearest center (true distance via vsqrt) and stores it pulled back by 0.1 along
   the probe; returns whether any hit was found. Shape, frame and arguments match; the remaining
   diffs are register choices: the RO_001813EC lui is hoisted to the top in $v1 (Original: $a2
   after s3 is set, and $v0 at the end), and the 0.1 scale goes through $v0 instead of $a2. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern float RO_001813C8[8];
extern float RO_001813EC;
extern char pathJudgeFunc[];
extern int ClipCollisionDirectCallBackDoubleSide(void *, Vec4 *, Vec4 *, int, int, int, int, int, void *, int);
extern Vec4 ZDirVector;
extern int getPathColiGroup(int);
extern void iosRotMatrixY(Vec4 *, float);

static inline void vu0_apply(void *d, void *m, void *v)
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
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

static inline void vu0_scale3(void *d, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}

static inline void vu0_add3(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline float vu0_dist(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

int getHitPosWayCollision(int path, Vec4 *out, Vec4 *center, float radius)
{
    Vec4 rot[4] __attribute__((aligned(16)));
    struct { char pad[0x40]; Vec4 pos; } hit __attribute__((aligned(16)));
    Vec4 dir __attribute__((aligned(16)));
    Vec4 end __attribute__((aligned(16)));
    float best = RO_001813EC;
    int i;

    out->q = center->q;
    for (i = 0; i < 8; i++) {
        float d;

        iosRotMatrixY(rot, RO_001813C8[i] * 0.017453292519943295f);
        vu0_apply(&dir, rot, &ZDirVector);
        vu0_scale3(&end, &dir, radius);
        vu0_add3(&end, &end, center);
        if (ClipCollisionDirectCallBackDoubleSide(&hit, center, &end, getPathColiGroup(path), 2, 0, 0, 0, pathJudgeFunc, 0) != 0) {
            d = vu0_dist(center, &hit.pos);
            if (d < best) {
                best = d;
                vu0_scale3(&dir, &dir, 0.099999995f);
                vu0_add3(out, &hit.pos, &dir);
            }
        }
    }
    return best != RO_001813EC;
}
#endif
