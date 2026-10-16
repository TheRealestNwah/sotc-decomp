void spriteSetTextureCoordinateST(char *s, float u, float v, float w, float h)
{
    *(unsigned long *)(s + 0x48) |= 0x8000L << 33;
    *(float *)(s + 0x20) = u;
    *(float *)(s + 0x24) = v;
    *(float *)(s + 0x28) = u + w;
    *(float *)(s + 0x2C) = v + h;
}
