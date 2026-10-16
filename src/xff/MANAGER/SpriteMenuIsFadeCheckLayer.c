int SpriteMenuIsFadeCheckLayer(unsigned char *o, int i)
{
    int off = i * 0x44;
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    char *e = *(char **)(c + 4) + off;
    float *f;
    switch (*(int *)(*(char **)e + 0xC)) {
    case 1:
        f = (float *)(e + 0x20);
        break;
    case 2:
        f = (float *)(e + 0x1C);
        break;
    case 3:
        f = (float *)(e + 0x1C);
        break;
    case 4:
        f = (float *)(e + 0x20);
        break;
    default:
        f = (float *)(e + 0xC);
        break;
    }
    if (*(float *)(e + 0x10) != *f) return 1;
    return 0;
}
