extern int D_0017A314;
extern int D_0017A318;
extern int D_0017A31C;
extern int D_0017A320;
extern float D_0017A3B0;
extern int D_0017A3B4;
extern float B_0018860C;
extern void setZFogFar(float);

static void func_00021FC0(void)
{
    if (D_0017A3B4) {
        D_0017A3B0 += B_0018860C;
        setZFogFar(D_0017A3B0);
        D_0017A3B4--;
        if (D_0017A31C < D_0017A314 || !D_0017A3B4)
            D_0017A314 = D_0017A31C;
        if (D_0017A320 < D_0017A318 || !D_0017A3B4)
            D_0017A318 = D_0017A320;
    } else {
        if (D_0017A31C != D_0017A314)
            D_0017A314 = D_0017A31C;
        if (D_0017A320 != D_0017A318)
            D_0017A318 = D_0017A320;
    }
}
