extern int strlen(const char *s);
extern int func_0001C238(int c);

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

int iosConvertStringEUCtoID(unsigned char *dst, unsigned char *src)
{
    int i = 0;
    int len = strlen((char *)src);

    for (; i < len; i += 2) {
        *(short *)(dst + i) = font_id(sjis_to_jis(func_0001C238(*(unsigned short *)(src + i))));
    }
    dst[len] = 0;
    return len / 2;
}
