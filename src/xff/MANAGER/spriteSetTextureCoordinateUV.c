void spriteSetTextureCoordinateUV(char *s, float u, float v, float du, float dv)
{
    *(int *)(s + 0x10) = (int)u;
    *(int *)(s + 0x14) = (int)v;
    *(int *)(s + 0x18) = (int)(u + du);
    *(int *)(s + 0x1C) = (int)(v + dv);
    *(unsigned long *)(s + 0x48) &= ~(1UL << 48);
    *(float *)(s + 0x38) = du;
    *(float *)(s + 0x3C) = dv;
}
