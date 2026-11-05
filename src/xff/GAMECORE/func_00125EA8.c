extern int DldSysUndefSymbol;
extern void SetCharacterClassGazeAdditionChannelInfo(void *chr, unsigned int *channel, float x, float y);

#define RAD 57.29578f

static inline char *dldA(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline char *dldB(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static void func_00125EA8(char *chr, char *arg, int flag, float x, float y)
{
    char *w = *(char **)(chr + 0x110C);
    unsigned int *ch = (unsigned int *)dldA(*(unsigned int **)(arg + 0x18));
    float *info = (float *)dldB(ch);
    *(float *)(w + 0xB4) = x;
    *(float *)(w + 0xB8) = y;
    if (0.0f <= x) {
        x = x * RAD / info[4];
        if (1.0f < x) x = 1.0f;
    } else {
        x = x * RAD / info[3];
        if (x < -1.0f) x = -1.0f;
    }
    if (0.0f <= y) {
        y = y * RAD / info[1];
        if (1.0f < y) y = 1.0f;
    } else {
        y = y * RAD / info[2];
        if (y < -1.0f) y = -1.0f;
    }
    if (!flag) {
        x = -x;
        y = -y;
    }
    SetCharacterClassGazeAdditionChannelInfo(chr, ch, x, y);
}
