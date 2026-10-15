float SpriteMenuGetFadeByLayer(unsigned char *o, int i)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    char *e = *(char **)(c + 4) + i * 0x44;
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
    return *f;
}
