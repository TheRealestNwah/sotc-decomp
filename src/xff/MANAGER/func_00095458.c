/* Parked: 193 diffs, same size (209 words). Right-aligned numeric text via the glyph table; control flow matches. Original: text in s7, glyphs in s6, &buf in fp (ours rotates s6/s7/fp); the 11-byte glyph-order table is copied from rodata with ldl/ldr. */
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
extern void spriteDrawSprite(int *, int, int, int, float, float, float, float, float, float);

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
    char *glyphs = dldData((unsigned int *)(text + 0x60));
    Table11 table;
    char buf[16];
    char pad[16];
    int i, j;
    float x;
    float f;

    if (width > 0 && glyphs != 0) {
        table = *(Table11 *)RO_00140670;
        iosSPrintf(buf, RO_00140680, *(int *)(text + 0xC));
        x = 0.0f;
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
                spriteSetPosition(spr, *(float *)(text + 0x1C) + x, *(float *)(text + 0x20) + 0.0f);
                spriteSetScale(spr, *(float *)(g + 0x24), *(float *)(g + 0x28));
                spriteSetTextureCoordinateUV(spr, *(float *)(g + 0x2C), *(float *)(g + 0x30), *(float *)(g + 0x34),
                                             *(float *)(g + 0x38));
                {
                    int dy = getDrawScreenHeight() >= 0x1C0 ? 0 : *(int *)(*(char **)layout + 8);
                    unsigned int flags = *(unsigned int *)(layout + 8);
                    float a = alpha;
                    if (!((flags >> 20) & 1) && (*(unsigned int *)(layout + 0x38) & 0x1FF))
                        a *= 0.59999996f;
                    spriteDrawSprite(spr, *(int *)(layout + 0x24), (flags >> 14) & 0xF, *(int *)(text + 0x70),
                                     *(float *)(layout + 0x1C), *(float *)(layout + 0x20) + (float)dy,
                                     *(float *)(layout + 0x28), *(float *)(layout + 0x2C),
                                     *(float *)(layout + 0x30), a);
                }
                f = *(float *)(g + 0x34);
                f *= 0.5f;
                x += f;
            } else {
                f = *(float *)(glyphs + 0x34);
                if (!(i > 0))
                    f *= 0.5f;
                x += f;
            }
        }
    }
}
#endif
