extern void iosUnitCurrentMatrix(void);
extern void iosRotCurrentMatrixX(float);
extern void iosRotCurrentMatrixY(float);
extern void iosRotCurrentMatrixZ(float);
extern void iosApplyCurrentMatrix(void *, void *);
extern float B_001486B0[4];
extern float B_001486C0[4];
extern float B_001486D0[4];
extern float D_00135B90[4];

void rotLightVector(int index, float *angle)
{
    float deg = 0.017453293f;

    iosUnitCurrentMatrix();
    iosRotCurrentMatrixY(angle[0] * deg);
    iosRotCurrentMatrixX(-angle[1] * deg);
    iosRotCurrentMatrixZ(angle[2] * deg);
    switch (index) {
    case 0:
        iosApplyCurrentMatrix(B_001486B0, D_00135B90);
        break;
    case 1:
        iosApplyCurrentMatrix(B_001486C0, D_00135B90);
        break;
    case 2:
        iosApplyCurrentMatrix(B_001486D0, D_00135B90);
        break;
    }
}
