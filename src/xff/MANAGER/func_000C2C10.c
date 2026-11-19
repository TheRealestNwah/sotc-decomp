typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } QVec;
typedef struct { float u, v; int a, b; } __attribute__((aligned(8))) UV;
extern float func_000C6DA0(void *);
extern int func_000C6F08(void *, void *);
extern void *ptclDisplayListGet(int);
extern void ptclDisplayListPut(int);
extern void ptclmanBegin(void);
extern void ptclmanBuildEnvPacket(void *, int, void *, void *, void *, float);
extern void ptclmanBuildMatPacket(int, float, float);
extern void ptclmanBuildVtxPacket(void *, int);
extern void ptclmanEnd(void);
extern void transMicroCode(int);
extern int D_001370E0;
extern float UnitMatrix[16];

#define DRAW_LIST()                                                                  do {                                                                                 float *mat = UnitMatrix;                                                         if (n != 0 && D_001370E0 != 0) {                                                     float u, v;                                                                      ptclDisplayListPut(n);                                                           transMicroCode(7);                                                               ptclmanBegin();                                                                  u = *(float *)(a2 + 0x58);                                                       v = *(float *)(a2 + 0x5C);                                                       uv = (UV){ u, v, 0, 0 };                                                         t = uv;                                                                          ptclmanBuildMatPacket(*(int *)(a1 + 0x14), u, v);                                ptclmanBuildEnvPacket(&t, 3, mat, 0, 0, 1.0f - *(float *)(a2 + 0x24));             ptclmanBuildVtxPacket(dl, n);                                                    ptclmanEnd();                                                                }                                                                            } while (0)

static void func_000C2C10(char *e, char *a1, char *a2)
{
    UV pad;
    UV t;
    UV uv;
    char *src;

    src = *(char **)(e + 0x128);
    if (*(int *)(a1 + 0x1B4) == 0) {
        char *dl; char *p; unsigned i; int n;
        dl = (char *)ptclDisplayListGet(*(int *)(a2 + 0x1C));
        if (dl != 0) {
        i = 0;
        n = 0;
        if (*(unsigned *)(e + 0x124) != 0) {
            p = dl;
            do {
                if (*(float *)(src + 0x40) != 0.0f && func_000C6F08(p + 0x20, src) != 0) {
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
                    p += 0x30;
                    n++;
                }
                i++;
                src = *(char **)(src + 0xA8);
            } while (i < *(unsigned *)(e + 0x124));
        }
        DRAW_LIST();
        }
    } else {
        char *dl; char *p; unsigned i; int n;
        dl = (char *)ptclDisplayListGet(*(int *)(a2 + 0x1C));
        if (dl != 0) {
        i = 0;
        n = 0;
        if (*(unsigned *)(e + 0x124) != 0) {
            p = dl;
            do {
                if (*(float *)(src + 0x40) != 0.0f) {
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
                    ((QVec *)(p + 0x20))->q = ((QVec *)(e + 0x10))->q;
                    p += 0x30;
                }
                i++;
                src = *(char **)(src + 0xA8);
            } while (i < *(unsigned *)(e + 0x124));
        }
        DRAW_LIST();
        }
    }
}
