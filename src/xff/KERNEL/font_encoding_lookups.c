static inline int sjis_to_jis(int code)
{
    unsigned long high = (code >> 8) & 0xFF;
    unsigned long low = code & 0xFF;
    if (high - 0x81 < 0x1FUL) {
        high -= 0x81;
    } else if (high - 0xE0 < 0x10UL) {
        high -= 0xC1;
    }
    high *= 2;
    if (low - 0x40 < 0x3FUL) {
        low -= 0x40;
    } else if (low - 0x80 < 0x1FUL) {
        low -= 0x41;
    } else if (low - 0x9F < 0x5EUL) {
        low -= 0x9F;
        high++;
    }
    return ((high + 1) << 8) + low + 0x2021;
}

static inline int font_id(int code)
{
    return (code >> 8) * 0x5E + (code & 0xFF) - 0xC3F;
}
typedef struct { char d[32]; } FontData;
extern FontData B_000C27B8[];

static inline char *font_data(FontData *out, int idx, int id)
{
    FontData *f = &B_000C27B8[id];
    char *r = *(char **)(f->d + 8) + idx * (*(int *)(f->d + 0x10) * *(int *)(f->d + 0x14));
    if (out != 0) {
        *out = *f;
    }
    return r;
}

char *iosGetFontDataWithJIS(FontData *out, int code, int font)
{
    return font_data(out, font_id(code), font);
}
char *iosGetFontDataWithSJIS(FontData *out, int code, int font)
{
    return font_data(out, font_id(sjis_to_jis(code)), font);
}
extern int func_0001C238(int);
char *iosGetFontDataWithEUC(FontData *out, int code, int font)
{
    return font_data(out, font_id(sjis_to_jis(func_0001C238(code))), font);
}

int iosGetFontIDWithSJIS(int code)
{
    return font_id(sjis_to_jis(code));
}
int iosGetFontIDWithEUC(int code)
{
    return font_id(sjis_to_jis(func_0001C238(code)));
}


