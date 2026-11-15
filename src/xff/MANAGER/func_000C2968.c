#ifdef NONMATCHING /* parked draft: 150 diffs, VU0 clamp run in place */
extern float func_000C6DA0(void *);
extern void iosGetSinCosf(void *, float);
extern void *ptclDisplayListGet(int);
extern void ptclDisplayListPut(int);
extern void ptclmanBegin(void);
extern void ptclmanBuildEnvPacket(long *, unsigned, int, int, float);
extern void ptclmanBuildMatPacket(int, float, float, long, long);
extern void ptclmanBuildVtxPacket(void *, int);
extern void ptclmanEnd(void);
extern void transMicroCode(int);
extern int D_001370E0;

void func_000C2968(char *a0, char *a1, char *a2, unsigned a3, int a4)
{
    long sp[2];
    float *fp = (float *)sp;
    char *dl;
    char *p;
    char *src;
    char *p2;
    int n;
    unsigned i;

    dl = (char *)ptclDisplayListGet(*(int *)(a2 + 0x1C));
    i = 0;
    if (dl != 0) {
        src = *(char **)(a0 + 0x128);
        n = 0;
        p = dl;
        p2 = dl + 0x20;
        if (*(unsigned *)(a0 + 0x124) != 0) {
            do {
                if (*(float *)(src + 0x40) != 0.0f) {
                    *(long long *)p = *(long long *)src;
                    *(long long *)(p + 8) = *(long long *)(src + 8);
                    *(float *)(p + 0xC) = *(float *)(a0 + 0x144) * *(float *)(src + 0x4C);
                    *(float *)(p + 0x10) = *(float *)(a0 + 0x70) * *(float *)(src + 0x68);
                    *(float *)(p + 0x14) = *(float *)(a0 + 0x74) * *(float *)(src + 0x70);
                    *(float *)(p + 0x18) = *(float *)(a0 + 0x78) * *(float *)(src + 0x78);
                    *(float *)(p + 0x1C) = *(float *)(a0 + 0x140) * *(float *)(src + 0x54) * func_000C6DA0(src);
                    __asm__ __volatile__("lqc2 vf7, 0x0(%0)\n"
                                         "vminiw.xyzw vf7, vf7, vf0w\n"
                                         "vmaxx.xyzw vf7, vf7, vf0x\n"
                                         "sqc2 vf7, 0x0(%0)\n"
                                         : : "r"(p) : "memory");
                    iosGetSinCosf(p2, *(float *)(src + 0x98) + 0.7853981f);
                    p += 0x30;
                    p2 += 0x30;
                    n++;
                }
                i++;
                src = *(char **)(src + 0xA8);
            } while (i < *(unsigned *)(a0 + 0x124));
        }
        if (n != 0 && D_001370E0 != 0) {
            ptclDisplayListPut(n);
            transMicroCode(7);
            ptclmanBegin();
            if (a3 != 7) {
                fp[0] = *(float *)(a2 + 0x58);
                fp[1] = *(float *)(a2 + 0x5C);
                fp[2] = 0;
                fp[3] = 0;
                ptclmanBuildMatPacket(*(int *)(a1 + 0x14), fp[0], fp[1], sp[0], sp[1]);
                ptclmanBuildEnvPacket(sp, a3, a4, 0, 1.0f - *(float *)(a2 + 0x24));
            } else {
                sp[0] = *(long *)(a2 + 0x12C);
                sp[1] = 0;
                ptclmanBuildMatPacket(*(int *)(a1 + 0x14), 1.0f, 1.0f, sp[0], sp[1]);
                ptclmanBuildEnvPacket(sp, 7, a4, 0, 1.0f - *(float *)(a2 + 0x24));
            }
            ptclmanBuildVtxPacket(dl, n);
            ptclmanEnd();
        }
    }
}
#endif
