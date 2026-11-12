typedef struct {
    int unk0;
    short count;
    short pad6;
} ClothList;

extern char *GetLayoutClass(void);
extern void iosTransMatrixF(float *, int, float, float, float);
extern void iosMulRotMatrixXInt16(float *, float *, int);
extern void getClothDynamics(char *, char *, int, void *, float, float, float *);
extern char func_0005D2C8[];

#ifdef NONMATCHING /* 113 diffs, 3 words over: matrix transpose in one asm block; loop flag handling and float constants */
int nico_execHorseBriddle(int arg1, float f0, float f1)
{
    float mat[16] __attribute__((aligned(16)));
    float inv[16] __attribute__((aligned(16)));
    float params[4] __attribute__((aligned(16)));
    char *lay = GetLayoutClass();
    ClothList *list;
    char *cloth;
    int i;
    int n;

    iosTransMatrixF(mat, *(int *)(lay + 0x158) + 0x40, 0.0f, 0.22987f, 0.0f);
    iosMulRotMatrixXInt16(mat, mat, -0x800);
    __asm__ __volatile__("lqc2 vf24, 0x30(%0)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%0)\n"
                         "lq $9, 0x10(%0)\n"
                         "lq $10, 0x20(%0)\n"
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
                         "sqc2 vf24, 0x0(%1)\n"
                         "sqc2 vf25, 0x10(%1)\n"
                         "sqc2 vf26, 0x20(%1)\n"
                         "sqc2 vf29, 0x30(%1)\n"
                         : : "r"(mat), "r"(inv) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
    list = *(ClothList **)(lay + 0x178);
    cloth = (char *)list->unk0;
    n = list->count;
    for (i = 0; i < n; ) {
        params[0] = (i & 1) ? 0.01f : -0.01f;
        params[1] = -0.59999996f;
        *(int *)&params[2] = (i & 1) ? 1 : -1;
        i++;
        getClothDynamics(cloth, lay, arg1, func_0005D2C8 + 0x18, f0, f1, params);
        cloth += 0x90;
    }
    return 0;
}
#endif
