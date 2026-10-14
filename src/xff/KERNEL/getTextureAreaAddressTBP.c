extern int B_00065550[];
int getTextureAreaAddressTBP(void)
{
    int *p = B_00065550;
    int a = p[0] * p[1] >> 6;
    int b = p[2] * p[3] >> 6;
    return a + b + b;
}
