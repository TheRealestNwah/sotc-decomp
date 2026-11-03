#ifdef NONMATCHING
/* a1/a2 register swap in the fallback (index 0) arm; otherwise matches. */
static inline int fadeCheck(unsigned char *c, int i)
{
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
    if (*(float *)(e + 0x10) != *f) return 1;
    return 0;
}

int SpriteMenuIsFadeCheckSelectLayer(unsigned char *o)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    int sel = *(int *)(c + 0xC);

    if (sel != -1) {
        return fadeCheck(c, sel);
    }
    return fadeCheck(c, 0);
}
#endif
