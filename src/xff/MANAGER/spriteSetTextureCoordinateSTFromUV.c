void spriteSetTextureCoordinateSTFromUV(char *s, float u, float v, float w, float h)
{
    char *texture = *(char **)(*(char **)s + 0x20);
    unsigned int dimensions = *(unsigned int *)(texture + 0x1C);
    float invWidth = 1.0f / (1 << ((dimensions >> 16) & 15));
    float invHeight = 1.0f / (1 << ((dimensions >> 20) & 15));
    *(unsigned long *)(s + 0x48) |= 0x8000L << 33;
    u += 0.5f;
    v += 0.5f;
    *(float *)(s + 0x20) = u * invWidth;
    *(float *)(s + 0x28) = (u + w) * invWidth;
    *(float *)(s + 0x24) = v * invHeight;
    *(float *)(s + 0x2C) = (v + h) * invHeight;
}
