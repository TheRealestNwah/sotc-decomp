extern int D_0017A31C;
extern int D_0017A320;
extern float D_0017A380;
extern float D_0017A3B0;
extern int D_0017A3B4;
extern float B_0018860C;

void SetSeamlessZFogDist(int start, int len)
{
    if (D_0017A31C == start && D_0017A320 == len)
        return;
    D_0017A31C = start;
    D_0017A320 = len;
    B_0018860C = (D_0017A380 * 0.5f + D_0017A380 * (float)(start + len - 1) - D_0017A3B0) / 15.0f;
    D_0017A3B4 = 15;
}
