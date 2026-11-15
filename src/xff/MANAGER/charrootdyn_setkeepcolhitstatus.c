#ifdef NONMATCHING /* parked draft: 92 diffs, VU0 runs in place */
typedef int s128 __attribute__((mode(TI)));

extern void DeleteTwoWayLink(void *);
extern void *GetLayoutClass(int);
extern void AddTwoWayLinkNext(void *, void *);

void charrootdyn_setkeepcolhitstatus(char *self, int *a1, float *a2, float *a3, char *obj, float f)
{
    float tmp[4];
    float f3, f1, sc;
    int iv;
    float *vp;
    char *link;
    int *dst;

    if (*(int *)(self + 0xFF0) != 0) {
        link = self + 0x1010;
        *(int *)(self + 0xFF0) = 0;
        DeleteTwoWayLink(link);
        *(int *)(self + 0xFF4) = 0;
    } else {
        link = self + 0x1010;
        *(int *)(self + 0xFF4) = 0;
    }
    *(int *)(self + 0xFF4) = *(int *)(obj + 0x30);
    if (*(int *)(obj + 0x30) != 0) {
        void *lc = GetLayoutClass(*(int *)(obj + 0x20));
        AddTwoWayLinkNext((char *)lc + 0x118, link);
        *(int *)(self + 0xFF0) = 1;
        dst = (int *)(self + 0xFF8);
        dst[0] = *(int *)(obj + 0x20);
        dst[1] = *(int *)(obj + 0x24);
        vp = (float *)(obj + 0x10);
    } else {
        void *lc = GetLayoutClass(a1[0]);
        AddTwoWayLinkNext((char *)lc + 0x118, link);
        *(int *)(self + 0xFF0) = 1;
        dst = (int *)(self + 0xFF8);
        dst[0] = a1[0];
        dst[1] = a1[1];
        vp = a3;
    }
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f3) : "r"(vp) : "$2", "memory");
    f1 = f3 - 1.0f;
    sc = f;
    if (f1 < 0.0f ? !(f1 > -0.01f) : !(f1 < 0.01f))
        sc = f * (1.0f / f1);
    iv = *(int *)&sc;
    __asm__ __volatile__("addiu %0, %1, 0x1000" : "=r"(dst) : "r"(self));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :  : "r"(vp), "r"(iv), "r"(tmp) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :  : "r"(a2), "r"(tmp), "r"(dst) : "memory");
}
#endif
