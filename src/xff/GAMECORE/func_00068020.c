extern float D_0017AD1C, D_0017AD20, D_0017AD24, D_0017AD28;
extern int D_0017AD2C, D_0017AD30;
extern void setLoadMapOffset(float, float, int, int);

void func_00068020(void)
{
    float d;

    if (D_0017AD24 != D_0017AD1C)
        D_0017AD1C = D_0017AD1C + (D_0017AD24 - D_0017AD1C) * 0.6f;
    if (D_0017AD28 != D_0017AD20)
        D_0017AD20 = D_0017AD20 + (D_0017AD28 - D_0017AD20) * 0.6f;
    d = D_0017AD24 - D_0017AD1C;
    if (d < 0.0f ? -1.0f < d : d < 1.0f)
        D_0017AD1C = D_0017AD24;
    d = D_0017AD28 - D_0017AD20;
    if (d < 0.0f ? -1.0f < d : d < 1.0f)
        D_0017AD20 = D_0017AD28;
    setLoadMapOffset(D_0017AD1C, D_0017AD20, D_0017AD2C, D_0017AD30);
}
