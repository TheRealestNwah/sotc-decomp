#ifdef NONMATCHING /* parked draft: 152 diffs, VU0 runs in place */
extern char *GetLayoutClass(int);
extern char *getLayoutClassCollisionIndepSurfBoundary(char *, int, int);
extern void GetCollisionDBVertexPoint(int **, int *, int);
extern long long *GetCollisionDBAttributeAdr(int *);

int CheckCollisionInsideOfSurfaceXZ(long long *out, int obj, float *pos)
{
    int key[2];
    int *vp[4];
    float d0[4];
    float d1[4];
    float d2[4];
    float s, t;
    float f1, f2, f3;
    char *cls;
    char *grp;
    char *b;
    int i, n;
    int *pa;

    cls = GetLayoutClass(obj);
    if (cls[0x1B8] == 0)
        return 0;
    if (cls[0x1BB] == 0)
        return 0;
    grp = *(char **)(*(char **)(*(char **)(cls + 0x184) + 0x20) + 8);
    n = *(int *)(grp + 0x10);
    if (n > 0) {
        for (i = 0; i < n; i++) {
            b = getLayoutClassCollisionIndepSurfBoundary(cls, 0, i);
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                                 : "=f"(f1) : "r"(b), "r"(pos) : "$2", "memory");
            f2 = *(float *)(b + 0xC);
            f2 = f2 * f2;
            if (f1 < f2) {
                key[0] = obj;
                key[1] = i | 0x80000000;
                GetCollisionDBVertexPoint(vp, key, 0);
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                                 :  : "r"(vp[1]), "r"(vp[0]), "r"(d0) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                                 :  : "r"(vp[2]), "r"(vp[0]), "r"(d1) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                                 :  : "r"(pos), "r"(vp[0]), "r"(d2) : "memory");
                d0[3] = 0.0f;
                d1[3] = 0.0f;
                d2[3] = 0.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "lqc2 vf7, 0x0(%3)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf8, vf6, vf5\n"
                         "vsub.w vf8, vf8, vf8\n"
                         "vopmula.xyz ACC, vf8, vf6\n"
                         "vopmsub.xyz vf9, vf6, vf8\n"
                         "vsub.w vf9, vf9, vf9\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf7\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f2) : "r"(d0), "r"(d1), "r"(d2) : "$2", "memory");
    __asm__ __volatile__("vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf5\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f3) :  : "$2", "memory");
                s = f2 / f3;
    __asm__ __volatile__("vopmula.xyz ACC, vf8, vf5\n"
                         "vopmsub.xyz vf9, vf5, vf8\n"
                         "vsub.w vf9, vf9, vf9\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf7\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f2) :  : "$2", "memory");
    __asm__ __volatile__("vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf6\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f3) :  : "$2", "memory");
                t = f2 / f3;
                if (s > -0.00001f && t > -0.00001f && s + t - 1.0f < 0.00001f) {
                    *out = *GetCollisionDBAttributeAdr(key);
                    return 1;
                }
            }
        }
    }
    return 0;
}
#endif
