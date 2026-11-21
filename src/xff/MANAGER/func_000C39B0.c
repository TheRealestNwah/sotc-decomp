/* Parked: 23 diffs. Builds a particle display list: for each live particle with a projected position writes a vertex record, then builds the matrix, brightness-clamped env and vertex packets and returns the list. Remaining: register swaps only (i/n in s5/s6, dl in s6/s7), mul.s/mfc1 order at 0x134 and the second branch UV stack slot (0x60 vs 0x80). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } QVec;
typedef struct { float u, v; int a, b; } __attribute__((aligned(8))) UV;
typedef struct { float a, b, c, d; } __attribute__((aligned(8))) Env;
extern float func_000C6DA0(void *);
extern void *ptclDisplayListGet(int);
extern void ptclDisplayListPut(int);
extern void ptclmanBegin(void);
extern void ptclmanBuildEnvPacket(void *, int, void *, void *, void *, float);
extern void ptclmanBuildMatPacket(int, float, float);
extern void ptclmanBuildVtxPacket(void *, int);
extern void ptclmanEnd(void);
extern void transMicroCode(int);
extern float gluGetBrightness(void *);
extern void iosScaleMatrix(float *, float, float, float);
extern int D_001370E0;
extern float B_00149A00[16];

static inline void mulMatrix(float *d, float *a, float *b)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "lqc2 vf24, 0x0(%2)\n"
                         "lqc2 vf25, 0x10(%2)\n"
                         "lqc2 vf26, 0x20(%2)\n"
                         "lqc2 vf27, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf27, 0x30(%0)\n"
                         ".set reorder\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecPos(char *out, char *v, char *a, char *p, float d, float t, float s)
{
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "qmtc2.ni %4, vf4\n"
                         "lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf9, 0x0(%3)\n"
                         "qmtc2.ni %5, vf5\n"
                         "qmtc2.ni %6, vf6\n"
                         "vmulx.xyz vf11, vf7, vf4x\n"
                         "vaddx.xyz vf11, vf8, vf11x\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "vsub.xyz vf10, vf9, vf11\n"
                         "vmulx.xyz vf11, vf7, vf6x\n"
                         "vsub.xyz vf10, vf10, vf11\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(a), "r"(p), "r"(d), "r"(t), "r"(s) : "a2");
}

static inline int calcPos(char *out, char *src)
{
    char *o = out;
    float t;
    float s;

    t = *(float *)(src + 0x98);
    if (*(float *)(src + 0x44) - t < *(float *)(src + 0xA0)) {
        t = *(float *)(src + 0x44) - *(float *)(src + 0xA0);
    }
    if (0.0f < t) {
        register float h asm("$f0") = 0.5f;
        vecPos(o, src + 0x20, src + 0x30, src, *(float *)(src + 0x44) - t, t, t * h * t);
        return 1;
    }
    return 0;
}

static inline void setParticle(char *p, char *e, char *src)
{
    ((QVec *)p)->q = ((QVec *)src)->q;
    *(float *)(p + 0xC) = *(float *)(e + 0x144) * *(float *)(src + 0x4C);
    *(float *)(p + 0x10) = *(float *)(e + 0x70) * *(float *)(src + 0x68);
    *(float *)(p + 0x14) = *(float *)(e + 0x74) * *(float *)(src + 0x70);
    *(float *)(p + 0x18) = *(float *)(e + 0x78) * *(float *)(src + 0x78);
    *(float *)(p + 0x1C) = *(float *)(e + 0x140) * *(float *)(src + 0x54) * func_000C6DA0(src);
    __asm__ __volatile__("lqc2 vf7, 0x0(%0)\n"
                         "vminiw.xyzw vf7, vf7, vf0w\n"
                         "vmaxx.xyzw vf7, vf7, vf0x\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(p + 0x10) : "memory");
}

static void func_000C39B0(char *e, char *a1, char *a2)
{
    float m[16] __attribute__((aligned(16)));
    Env env;
    char *col;
    char *dl;
    char *src;
    char *p;
    char *q;
    unsigned i;
    int n;
    float b;
    float c;

    src = *(char **)(e + 0x128);
    if (*(int *)(a1 + 0x1B4) == 0) {
        dl = (char *)ptclDisplayListGet(*(int *)(a2 + 0x1C));
        b = *(float *)(a2 + 0xB8) * gluGetBrightness(e + 0x80);
        c = 1.0f < b ? 1.0f : (b < 0.0f ? 0.0f : b);
        if (dl != 0) {
            n = 0;
            i = 0;
            env = (Env){ c, 1.0f - c, 0.0f, *(float *)(a2 + 0xB4) };
            if (*(unsigned *)(e + 0x124) != 0) {
                p = dl;
                q = dl + 0x20;
                do {
                    if (*(float *)(src + 0x40) != 0.0f) {
                        if (calcPos(q, src)) {
                            setParticle(p, e, src);
                            p += 0x30;
                            q += 0x30;
                            n++;
                        }
                    }
                    i++;
                    src = *(char **)(src + 0xA8);
                } while (i < *(unsigned *)(e + 0x124));
            }
            iosScaleMatrix(m, *(float *)(a2 + 0x50), *(float *)(a2 + 0x54), 1.0f);
            mulMatrix(m, B_00149A00, m);
            col = e + 0x90;
            if (n != 0 && D_001370E0 != 0) {
                ptclDisplayListPut(n);
                transMicroCode(7);
                ptclmanBegin();
                {
                    UV pad;
                    UV t;
                    UV uv;
                    float u = *(float *)(a2 + 0x58);
                    float v = *(float *)(a2 + 0x5C);
                    uv = (UV){ u, v, 0, 0 };
                    t = uv;
                    ptclmanBuildMatPacket(*(int *)(a1 + 0x14), u, v);
                    ptclmanBuildEnvPacket(&t, 5, m, col, &env, 1.0f - *(float *)(a2 + 0x24));
                }
                ptclmanBuildVtxPacket(dl, n);
                ptclmanEnd();
            }
        }
    } else {
        dl = (char *)ptclDisplayListGet(*(int *)(a2 + 0x1C));
        b = *(float *)(a2 + 0xB8) * gluGetBrightness(e + 0x80);
        c = 1.0f < b ? 1.0f : (b < 0.0f ? 0.0f : b);
        if (dl != 0) {
            n = 0;
            i = 0;
            env = (Env){ c, 1.0f - c, 0.0f, *(float *)(a2 + 0xB4) };
            if (*(unsigned *)(e + 0x124) != 0) {
                p = dl;
                do {
                    if (*(float *)(src + 0x40) != 0.0f) {
                        setParticle(p, e, src);
                        ((QVec *)(p + 0x20))->q = ((QVec *)(e + 0x10))->q;
                        p += 0x30;
                        n++;
                    }
                    i++;
                    src = *(char **)(src + 0xA8);
                } while (i < *(unsigned *)(e + 0x124));
            }
            iosScaleMatrix(m, *(float *)(a2 + 0x50), *(float *)(a2 + 0x54), 1.0f);
            mulMatrix(m, B_00149A00, m);
            col = e + 0x90;
            if (n != 0 && D_001370E0 != 0) {
                ptclDisplayListPut(n);
                transMicroCode(7);
                ptclmanBegin();
                {
                    UV t;
                    UV uv;
                    float u = *(float *)(a2 + 0x58);
                    float v = *(float *)(a2 + 0x5C);
                    uv = (UV){ u, v, 0, 0 };
                    t = uv;
                    ptclmanBuildMatPacket(*(int *)(a1 + 0x14), u, v);
                    ptclmanBuildEnvPacket(&t, 5, m, col, &env, 1.0f - *(float *)(a2 + 0x24));
                }
                ptclmanBuildVtxPacket(dl, n);
                ptclmanEnd();
            }
        }
    }
}
#endif
