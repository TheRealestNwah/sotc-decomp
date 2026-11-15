#ifdef NONMATCHING /* parked draft: 155 diffs, mirrors func_0009A7C0 with byte-count header */
extern void *getLayoutClassCollisionIndepSurfBoundary(int, int, int);
extern void func_000999E0(int *, int *, int, int, int);
extern void EntryModifiedManager(void *, int);
extern int CheckCollisionFinderExistData(int, int, int);
extern void EntryCollisionFinder(int, int, int);

void func_0009A508(int *ctx, int *list, int idx)
{
    int n;
    unsigned short *p;
    int layout, key;
    int *pos;
    float rad;
    char *cls;
    char *ent;
    char *rec;
    float *dst;
    float f1, f0;
    int p1[4];
    int p2[4];
    int *v0p, *v1p, *v2p;
    char *s;
    int packed;
    int (*cb1)(int, int);
    int (*cb2)(int *, int);

    layout = ctx[2];
    pos = (int *)ctx[8];
    rad = *(float *)((char *)ctx + 0x18);
    n = *(unsigned char *)(list[1] + idx * 4) - 1;
    p = (unsigned short *)(list[0] + (*(unsigned *)(list[1] + idx * 4) >> 8) * 2);
    if (n != -1) {
        do {
            key = *p;
            s = (char *)getLayoutClassCollisionIndepSurfBoundary(layout, 0, key);
            f0 = *(float *)(s + 0xC) + rad;
            f0 = f0 * f0;
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                             : "=f"(f1) : "r"(s), "r"(pos) : "$2", "memory");
            if (f1 < f0) {
                cb1 = (int (*)(int, int))ctx[10];
                if (cb1 == 0 || cb1(ctx[3], ctx[12]) != 0) {
                    cls = (char *)layout;
                    ent = (char *)*(int *)(*(int *)(cls + 0x174) + 0x24) + 0x30;
                    rec = (char *)*(int *)(ent + 0x14);
                    dst = (float *)(rec + key * 16);
                    if (*(unsigned char *)(*(int *)(ent + 8) + key) == 0) {
                        func_000999E0(p1, p2, layout, 0, key);
                        v0p = (int *)p1[0];
                        v1p = (int *)p1[1];
                        v2p = (int *)p2[0];
                        __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n"
                         "vsub.xyzw vf31, vf29, vf30\n"
                         "vmove.xyzw vf18, vf31\n"
                         "vmove.xyzw vf29, vf30\n"
                             :  : "r"(v1p) : "memory");
                        __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n"
                         "vsub.xyzw vf31, vf29, vf30\n"
                         "vmove.xyzw vf29, vf18\n"
                         "vmove.xyzw vf30, vf31\n"
                         "vopmula.xyz ACC, vf29, vf30\n"
                         "vopmsub.xyz vf31, vf30, vf29\n"
                         "vsub.w vf31, vf31, vf31\n"
                         "vmove.xyzw vf29, vf31\n"
                         "vmul.xyz vf7, vf29, vf29\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf29, vf29, Q\n"
                         "vmove.xyzw vf31, vf29\n"
                         "sqc2 vf31, 0x0(%1)\n"
                             :  : "r"(v2p), "r"(dst) : "memory");
                        __asm__ __volatile__("lqc2 vf4, 0x0(%0)\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf5, vf4, vf5\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "vsubw.xyzw vf6, vf0, vf0w\n"
                         "vsubx.w vf4, vf6, vf5x\n"
                         "sqc2 vf4, 0x0(%0)\n"
                             :  : "r"(dst), "r"(v0p) : "memory");
                                                EntryModifiedManager(ent, key);
                    }
                    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "vaddw.x vf6, vf6, vf5w\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                             : "=f"(f1) : "r"(dst), "r"(pos) : "$2", "memory");
                    f0 = 0.0f;
                    if (f1 < 0.0f)
                        f0 = -f1;
                    else
                        f0 = f1;
                    if (f0 < rad) {
                        cb2 = (int (*)(int *, int))ctx[11];
                        packed = key | 0x80000000;
                        p1[0] = ctx[1];
                        p1[1] = packed;
                        if (cb2 == 0 || cb2(p1, ctx[12]) != 0) {
                            if (CheckCollisionFinderExistData(ctx[0], ctx[13], key) == 0)
                                EntryCollisionFinder(ctx[0], ctx[1], packed);
                        }
                    }
                }
            }
            p++;
            n--;
        } while (n != -1);
    }
}
#endif
