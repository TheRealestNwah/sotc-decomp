/* Parked: 8 diffs (ee-gcc 2.96 -O2 -G0).
 * Remaining: i and n swap registers (v1/a0) around the outer loop, and the
 * mfc1 of half lands in v1 instead of t0.
 */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef union { s128 q[4]; float f[16]; } Mat4;

typedef struct Seg {
    short type;
    char pad2[6];
    int count;
    char padC[0x1C];
    float *len;
} Seg;

typedef struct Chain {
    Seg *seg;
    char pad4[8];
    char *pts;
    char pad10[0x80];
} Chain;

typedef struct ChainHdr {
    Chain *list;
    short count;
} ChainHdr;

extern char *GetLayoutClass(void *);
extern float GetDistanceSquare(float *, float *);
extern float GetArbitraryDirectionInverseMatrix(float *, float *, float *, float *);
extern void SetGeometryPointerChainPos(void *, void *, int, float);

int CheckClothChainDetect(void *a0, void *a1, float *pos, float r)
{
    ChainHdr *h;
    Chain *c;
    int n;
    int i;

    h = *(ChainHdr **)(GetLayoutClass(a1) + 0x178);
    n = h->count;
    c = h->list;
    for (i = 0; i < n; i++, c++) {
        Seg *s = c->seg;
        float *p;
        register float len asm("$f26");
        register float bestT asm("$f21");
        register float bestD asm("$f20");
        int best;
        int j;
        register float half asm("$f23");
        float lim;

        if (s->type != 1)
            continue;
        best = -1;
        j = 0;
        p = *(float **)(*(char **)&c->pts + 0x10);
        len = s->len[1];
        bestT = 0.0f;
        bestD = bestT;
        if (s->count > 0) {
        half = 0.5f;
        { float t = len * half + r; lim = t * t; }
        do {
            float *q = p + 4;
            Vec4 mid;
            Mat4 m;
            Mat4 m2;
            Vec4 l;
            float seg;
            float z;
            float d;

            __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                                 "lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsubx.w vf8, vf0, vf7x\n"
                                 "vmulax.xyz ACC, vf5, vf7x\n"
                                 "vmaddw.xyz vf5, vf6, vf8w\n"
                                 "sqc2 vf5, 0x0(%3)\n"
                                 : : "r"(half), "r"(p), "r"(q), "r"(mid.f) : "memory");
            if (!(GetDistanceSquare(pos, mid.f) < lim))
                continue;
            seg = GetArbitraryDirectionInverseMatrix(m.f, m2.f, p, q);
            if (seg < 0.0f)
                continue;
            __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                                 "lqc2 vf14, 0x0(%2)\n"
                                 "lqc2 vf15, 0x10(%2)\n"
                                 "lqc2 vf16, 0x20(%2)\n"
                                 "lqc2 vf17, 0x30(%2)\n"
                                 "vmulax.xyzw ACC, vf14, vf8x\n"
                                 "vmadday.xyzw ACC, vf15, vf8y\n"
                                 "vmaddaz.xyzw ACC, vf16, vf8z\n"
                                 "vmaddw.xyzw vf10, vf17, vf8w\n"
                                 "sqc2 vf10, 0x0(%0)\n"
                                 : : "r"(l.f), "r"(pos), "r"(m.f) : "memory");
            z = l.f[2];
            if (z < -r)
                continue;
            if (seg + r < z)
                continue;
            if (r * r < l.f[0] * l.f[0] + l.f[1] * l.f[1])
                continue;
            if (!(z < 0.0f) && !(seg < z)) {
                best = j;
                bestT = z;
                break;
            }
            if (best < 0) {
                best = j;
                if (z < 0.0f) {
                    bestD = -z;
                    bestT = z;
                } else if (seg < z) {
                    bestD = z - seg;
                    bestT = z;
                }
            } else {
                if (z < 0.0f)
                    d = -z;
                else if (seg < z)
                    d = z - seg;
                else
                    continue;
                if (d < bestD) {
                    bestD = d;
                    bestT = z;
                    best = j;
                }
            }
        } while (p += 4, ++j < s->count);
        }
        if (best >= 0) {
            SetGeometryPointerChainPos(a0, a1, i, bestT + best * len);
            return 1;
        }
    }
    return 0;
}
#else
extern int CheckClothChainDetect(void *a0, void *a1, float *pos, float r);
#endif
