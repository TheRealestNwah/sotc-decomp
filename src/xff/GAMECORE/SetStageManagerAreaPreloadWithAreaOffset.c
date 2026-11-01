typedef union { float f[4]; int q __attribute__((mode(TI))); } Vec4;
typedef struct {
    char pad0[0x14];
    float cellX, cellZ;
    char pad1C[0x18];
    int width, height;
} AreaGrid;
extern AreaGrid *D_0017A868;
extern Vec4 ZUnitVector;
extern void PauseCamFinalizer(int);
extern void SetCamFinalizerGeometry(Vec4 *, Vec4 *);
void SetStageManagerAreaPreloadWithAreaOffset(int index, Vec4 *offset)
{
    Vec4 position;
    AreaGrid *grid;
    int column;
    PauseCamFinalizer(1);
    grid = D_0017A868;
    column = index % grid->width;
    index /= grid->width;
    position.f[0] = -(((float)column - (float)grid->width * 0.5f) * grid->cellX + grid->cellX * 0.5f);
    position.f[1] = 0;
    position.f[2] = ((float)index - (float)grid->height * 0.5f) * grid->cellZ + grid->cellZ * 0.5f;
    position.f[3] = 1;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&position), "r"(offset) : "memory");
    SetCamFinalizerGeometry(&position, &ZUnitVector);
}
