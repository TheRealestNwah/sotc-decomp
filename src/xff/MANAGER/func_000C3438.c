/* NONMATCHING: byte-identical only with an explicit asm nop standing in for the
 * do-while loop's alignment nop. A real do/while/for loop makes gcc hoist the
 * 0.0f and 0.78539816f constants out of the loop (147 diffs). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } QVec;
typedef struct { float u, v; int a, b; } __attribute__((aligned(8))) UV;
extern float func_000C6DA0(void *);
extern void iosGetSinCosf(void *, float);
extern void *ptclDisplayListGet(int);
extern void ptclDisplayListPut(int);
extern void ptclmanBegin(void);
extern void ptclmanBuildEnvPacket(void *, int, void *, void *, void *, float);
extern void ptclmanBuildMatPacket(int, float, float);
extern void ptclmanBuildVtxPacket(void *, int);
extern void ptclmanEnd(void);
extern void transMicroCode(int);
extern int D_001370E0;

static inline void buildPackets(char *a1, char *a2, void *a3, int type)
{
    UV t;
    UV uv;
    UV pad;
    if (type != 7) {
        float u = *(float *)(a2 + 0x58);
        float v = *(float *)(a2 + 0x5C);
        uv = (UV){ u, v, 0, 0 };
        t = uv;
        ptclmanBuildMatPacket(*(int *)(a1 + 0x14), u, v);
    } else {
        float u = *(float *)(a2 + 0x12C);
        float v = *(float *)(a2 + 0x130);
        uv = (UV){ u, v, 0, 0 };
        t = uv;
        ptclmanBuildMatPacket(*(int *)(a1 + 0x14), 1.0f, 1.0f);
    }
    ptclmanBuildEnvPacket(&t, type, a3, 0, 0, 1.0f - *(float *)(a2 + 0x24));
}

static void func_000C3438(char *e, char *a1, char *a2, void *a3)
{
    char *dl;
    char *src;
    char *p;
    unsigned i;
    int n;
    float inv;
    float k;

    dl = (char *)ptclDisplayListGet(*(int *)(a2 + 0x1C));
    if (dl != 0) {
        i = 0;
        n = 0;
        inv = 1.0f / *(float *)(a2 + 0x128);
        src = *(char **)(e + 0x128);
        if (*(unsigned *)(e + 0x124) != 0) {
            p = dl;
            __asm__ __volatile__("nop");
        loop:
                if (*(float *)(src + 0x40) != 0.0f) {
                    k = (float)(int)(*(float *)(src + 0x90) * inv);
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
                    n++;
                    iosGetSinCosf(p + 0x20, *(float *)(src + 0x98) + 0.78539816f);
                    *(float *)(p + 0x28) = (float)(int)(*(float *)(src + 0x90) - k * *(float *)(a2 + 0x128)) * *(float *)(a2 + 0x12C);
                    *(float *)(p + 0x2C) = k * *(float *)(a2 + 0x130);
                    p += 0x30;
                    __asm__ __volatile__("");
                }
                src = *(char **)(src + 0xA8);
            if (++i < *(unsigned *)(e + 0x124)) goto loop;
        }
        if (n != 0 && D_001370E0 != 0) {
            ptclDisplayListPut(n);
            transMicroCode(7);
            ptclmanBegin();
            buildPackets(a1, a2, a3, 7);
            ptclmanBuildVtxPacket(dl, n);
            ptclmanEnd();
        }
    }
}
#endif
