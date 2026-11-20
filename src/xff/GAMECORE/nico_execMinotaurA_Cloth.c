/* Minotaur A cloth update: for two cloth anchor matrices (layout +0x158 plus 0x240 / 0x280, scaled by the layout size at +0x90, the second rotated 0xE38 about X) builds the matrix with iosTransMatrixF and the two rotate calls, inverts it with the VU0 transpose block into the next slot, stores two size-scaled parameters beside each, then runs getClothDynamics for every cloth in the list at +0x178 (stride 0x90), passing func_0005E108 unless the first entry's flag is nonzero. The matrices and the int 2 sit in one frame struct. */
extern char *GetLayoutClass(void);
extern void iosTransMatrixF(void *, void *, float, float, float);
extern void iosMulRotMatrixYInt16(void *, void *, int);
extern void iosMulRotMatrixXInt16(void *, void *, int);
extern void getClothDynamics(void *, void *, float, float, int, void *, void *);
extern void func_0005E108(void);

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

void nico_execMinotaurA_Cloth(int unused, int a1, float f25, float f24)
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
    float f20;
    float nz;
    float z;
    char *cl;
    char *p;
    char *m;
    float h;
    int n;

    lay = GetLayoutClass();
    L.two = 2;
    z = 0.0f;
    nz = -z;
    f20 = ((PU *)(lay + 0x90))->f;
    m = (char *)L.m1;
    iosTransMatrixF(L.m1, ((PU *)(lay + 0x158))->p + 0x240, f20 * nz, f20 * z, 2.0f * f20);
    iosMulRotMatrixYInt16(L.m1, L.m1, 0);
    iosMulRotMatrixXInt16(L.m1, L.m1, 0);
    matInverse(L.im1, (float *)m);
    L.v80[1] = f20 * -6.0f;
    L.v80[0] = f20 * 20.25f * f20 * 0.25f;
    h = ((PU *)(lay + 0x90))->f;
    m = (char *)L.m2;
    iosTransMatrixF(L.m2, ((PU *)(lay + 0x158))->p + 0x280, h * nz, h * -0.6f, h * 1.8f);
    iosMulRotMatrixYInt16(L.m2, L.m2, 0);
    iosMulRotMatrixXInt16(L.m2, L.m2, 0xE38);
    matInverse(L.im2, (float *)m);
    L.v110[1] = h * -6.0f;
    L.v110[0] = h * 31.36f * h * 0.25f;
    cl = ((PU *)(lay + 0x178))->p;
    n = *(short *)(cl + 4);
    p = *(char **)cl;
    if (n > 0) {
        int i = n;
        do {
            getClothDynamics(p, lay, f25, f24, a1, (**(short **)p != 0) ? 0 : (void *)func_0005E108, &L);
            p += 0x90;
        } while (--i != 0);
    }
}

