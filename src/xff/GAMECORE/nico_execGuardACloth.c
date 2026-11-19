extern char *GetLayoutClass();
extern void iosTransMatrixF(void *, void *, float, float, float);
extern void iosMulRotMatrixYInt16(void *, void *, int);
extern void iosMulRotMatrixXInt16(void *, void *, int);
extern void getClothDynamics(void *, void *, float, float, int, void *, void *);
extern void func_0005E848(void);
extern int GetGeometryPointerObject(void *);

static inline void matInverse(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

/* Read through a union so gcc keeps each load after the preceding float stores, like the Original. */
typedef union { char *p; float f; } PU;

/* Runs the Guard A cloth: when the layout has a geometry object, builds two collision frames (and inverses) from its
   bones at 0x300 and 0x280, scaled by its size, then steps every cloth strip with getClothDynamics. The geometry
   layout and strip pointer are pinned to $s1, as in the Original. */
void nico_execGuardACloth(int unused, int a1, float f24, float f23)
{
    struct {
        float m1[16];
        float im1[16];
        float v80[4];
        float m2[16];
        float im2[16];
        float v110[4];
        int two;
    } L __attribute__((aligned(16)));
    char *lay;
    register char *g __asm__("$17");
    float f20;
    float f21;
    char *cl;
    char *m;
    float h;
    register char *p __asm__("$17");
    int n;

    lay = GetLayoutClass();
    L.two = -1;
    if (*(int *)(lay + 0x124) != 0) {
        int geo = GetGeometryPointerObject(lay + 0xC0);
        if (geo != 0) {
            g = GetLayoutClass(geo);
            L.two = 2;
            f20 = ((PU *)(g + 0x90))->f;
            m = (char *)L.m1;
            {
                float y = f20 * 0.088f;
                iosTransMatrixF(L.m1, ((PU *)(g + 0x158))->p + 0x300, f20 * 0.149999997f, y, f20 * 0.036f);
            }
            iosMulRotMatrixYInt16(L.m1, L.m1, 0x4000);
            iosMulRotMatrixXInt16(L.m1, L.m1, 0);
            matInverse(L.im1, (float *)m);
            L.v80[1] = f20 * -0.29999998211860657f;
            L.v80[0] = f20 * 0.089999995f * f20 * 0.25f;
            h = ((PU *)(g + 0x90))->f;
            m = (char *)L.m2;
            f21 = h * 0.25f;
            iosTransMatrixF(L.m2, ((PU *)(g + 0x158))->p + 0x280, f21, h * 0.12f, h * -0.17999999225139618f);
            iosMulRotMatrixYInt16(L.m2, L.m2, 0x4000);
            iosMulRotMatrixXInt16(L.m2, L.m2, 0);
            matInverse(L.im2, (float *)m);
            L.v110[1] = h * -0.5f;
            L.v110[0] = f21 * h * 0.25f;
        }
    }
    if (L.two >= 0) {
        cl = ((PU *)(lay + 0x178))->p;
        n = *(short *)(cl + 4);
        p = *(char **)cl;
        if (n > 0) {
            int i = n;
            do {
                getClothDynamics(p, lay, f24, f23, a1, (void *)func_0005E848, &L);
                p += 0x90;
            } while (--i != 0);
        }
    }
}
