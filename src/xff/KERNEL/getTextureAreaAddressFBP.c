extern int B_00065550[];
int getTextureAreaAddressFBP(void)
{
    int *p = B_00065550;
    int a = p[0] * p[1] >> 11;
    int b = p[2] * p[3] >> 11;
    return a + b + b;
}
