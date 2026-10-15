typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern int B_00147A80[];
extern Vec4 B_00147A70;
extern float D_00130458;
extern void gluGetLookAtPosition(Vec4 *, float);

void cameraBlurClearIntensityArray(void)
{
    int i;
    Vec4 p;
    for (i = 7; i >= 0; i--)
        B_00147A80[i] = 0;
    gluGetLookAtPosition(&p, D_00130458);
    B_00147A70.q = p.q;
}
