extern char *GetLayoutClass();
extern void iosTransMatrixF(void *, void *, float, float, float);
extern void iosMulRotMatrixYInt16(void *, void *, int);
extern void iosMulRotMatrixXInt16(void *, void *, int);
extern void getClothDynamics(void *, void *, float, float, int, void *, void *);
extern void func_0005D888(void);
extern void T_0005DAB8(void);

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

/* Reading the layout pointers through a union with a float keeps them after the float parameter stores, like the Original. */
typedef union { char *p; float f; } PU;

/* Horse cloth update: builds three anchor matrices (layout +0x158 plus 0x5C0, 0x580 and 0x40, rotated about X) and their inverses with three parameters, then runs getClothDynamics for every cloth in the list at +0x178 (stride 0x90): the first two with T_0005DAB8 and the anchor data, the rest with func_0005D888. */
void nico_execHorseCloth(int unused, int a1, float f23, float f22)
{
    struct {
        float m1[16];
        float im1[16];
        float m2[16];
        float im2[16];
        float m3[16];
        float im3[16];
        float v[4];
    } L __attribute__((aligned(16)));
    char *lay;
    char *cl;
    char *p;
    int n;
    int i;

    lay = GetLayoutClass();
    iosTransMatrixF(L.m1, ((PU *)(lay + 0x158))->p + 0x5C0, 0.0f, 0x1.47ae1p-5f, 0x1.999998p-5f);
    iosMulRotMatrixXInt16(L.m1, L.m1, 0xB00);
    matInverse(L.im1, L.m1);
    L.v[0] = 0x1.47ae1p-5f;
    iosTransMatrixF(L.m2, ((PU *)(lay + 0x158))->p + 0x580, 0.0f, -0x1.47ae1p-4f, 0.0f);
    iosMulRotMatrixXInt16(L.m2, L.m2, 0xF00);
    matInverse(L.im2, L.m2);
    L.v[1] = 0x1.8c7e26p-5f;
    iosTransMatrixF(L.m3, ((PU *)(lay + 0x158))->p + 0x40, 0.0f, 0x1.d70a3cp-3f, 0.0f);
    iosMulRotMatrixXInt16(L.m3, L.m3, -0xC00);
    matInverse(L.im3, L.m3);
    L.v[2] = 0x1.be0deap-4f;
    cl = ((PU *)(lay + 0x178))->p;
    n = *(short *)(cl + 4);
    p = *(char **)cl;
    i = 0;
    if (n > 0) {
        do {
            int t = i < 2;
            i++;
            if (t) {
                getClothDynamics(p, lay, f23, f22, a1, (void *)T_0005DAB8, &L);
            } else {
                getClothDynamics(p, lay, f23, f22, a1, (void *)func_0005D888, 0);
            }
            p += 0x90;
        } while (i < n);
    }
}
