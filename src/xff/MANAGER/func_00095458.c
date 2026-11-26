/* Parked: 11 diffs, same size (209 words) (23 before; flag -fno-strict-aliasing). spriteDrawSprite takes its six floats before the two ints (pri, then the text's 0x70 field), like func_00095218 and func_00099118. Earlier fixes: a real float `y` (zero, copied from x) for the `+ 0.0f` y offset (original keeps it in f23), alpha as the last float argument in a conditional (`cond ? alpha * 0.6f : alpha`), `fdy` converted before the layout loads, 0.6f, and the missing-glyph branch as `if (i > 0) x += w; else x += w * 0.5f`. Remaining: the string address setup order before the first iosSPrintf, and load scheduling around the two spriteSetPosition/spriteDrawSprite calls. */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern char RO_00140670[];
extern char RO_00140678[];
extern char RO_00140680[];
extern int getDrawScreenHeight(void);
extern int iosSPrintf(char *, const char *, ...);
extern unsigned int strlen(const char *);
extern char *strcpy(char *, const char *);
extern char *strcat(char *, const char *);
extern void spriteSetPosition(int *, float, float);
extern void spriteSetScale(int *, float, float);
extern void spriteSetTextureCoordinateUV(int *, float, float, float, float);
extern void spriteDrawSprite(int *, int, float, float, float, float, float, float, int, int);

typedef struct {
    char c[11];
} Table11;

static inline char *dldData(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) : 0;
}

void func_00095458(int *spr, char *layout, char *text, int width, float alpha)
{
    char *glyphs;
    char *g0;
    Table11 table;
    char buf[16];
    char pad[16];
    int i, j;
    float x;
    float y;
    float f;

    g0 = dldData((unsigned int *)(text + 0x60));
    glyphs = g0;
    if (width > 0 && glyphs != 0) {
        table = *(Table11 *)RO_00140670;
        iosSPrintf(buf, RO_00140680, *(int *)(text + 0xC));
        x = 0.0f;
        y = x;
        if (strlen(buf) < (unsigned int)width) {
            char n = strlen(buf);
            strcpy(pad, buf);
            buf[0] = 0;
            while (strlen(buf) < (unsigned int)(width - n))
                strcat(buf, RO_00140678);
            strcat(buf, pad);
        }
        for (i = 0; (unsigned int)i < strlen(buf); i++) {
            unsigned int found = -1;
            unsigned int k;
            for (k = 0; k < strlen(table.c); k++)
                found = (table.c[k] == buf[i]) ? k : found;
            if ((int)found >= 0) {
                char *g = glyphs + (found << 7);
                if (i > 0)
                    x += *(float *)(g + 0x34) * 0.5f;
                *spr = *(int *)(dldData((unsigned int *)g) + 0xC);
                spriteSetPosition(spr, *(float *)(text + 0x1C) + x, *(float *)(text + 0x20) + y);
                spriteSetScale(spr, *(float *)(g + 0x24), *(float *)(g + 0x28));
                spriteSetTextureCoordinateUV(spr, *(float *)(g + 0x2C), *(float *)(g + 0x30), *(float *)(g + 0x34),
                                             *(float *)(g + 0x38));
                {
                    int dy = getDrawScreenHeight() >= 0x1C0 ? 0 : *(int *)(*(char **)layout + 8);
                    float fdy = (float)dy;
                    unsigned int flags = *(unsigned int *)(layout + 8);
                    spriteDrawSprite(spr, *(int *)(layout + 0x24),
                                     *(float *)(layout + 0x1C), *(float *)(layout + 0x20) + fdy,
                                     *(float *)(layout + 0x28), *(float *)(layout + 0x2C),
                                     *(float *)(layout + 0x30),
                                     (!((flags >> 20) & 1) && (*(unsigned int *)(layout + 0x38) & 0x1FF)) ? alpha * 0.6f : alpha,
                                     (flags >> 14) & 0xF, *(int *)(text + 0x70));
                }
                f = *(float *)(g + 0x34);
                f *= 0.5f;
                x += f;
            } else {
                if (i > 0)
                    x += *(float *)(glyphs + 0x34);
                else
                    x += *(float *)(glyphs + 0x34) * 0.5f;
            }
        }
    }
}
#endif
