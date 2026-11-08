extern int strlen(const char *s);

#ifdef NONMATCHING
/* Parked: 66 words differ (register allocation and kanji pair layout) */
int iosConvertStringSJIStoEUC(unsigned char *dst, char *src)
{
    int i = 0;
    int len = strlen(src);
    unsigned char k[2];

    k[1] = 0;
    for (; i < len; dst++) {
        unsigned char c = *src++;
        i++;
        if (!(c & 0x80)) {
            *dst = c;
        } else if ((unsigned char)(c + 0x5F) < 0x3F) {
            *dst++ = 0x8E;
            *dst = c;
        } else {
            k[0] = c;
            k[1] = *src++;
            i++;
            if (k[1] < 0x9F) {
                k[0] = (unsigned char)(k[0] << 1) < 0x3F ? (k[0] << 1) - 0x61 : (k[0] << 1) + 0x1F;
                k[1] = k[1] < 0x7F ? k[1] + 0x61 : k[1] + 0x60;
            } else {
                k[0] = (unsigned char)(k[0] << 1) < 0x3F ? (k[0] << 1) - 0x60 : (k[0] << 1) + 0x20;
                k[1] = k[1] + 2;
            }
            *dst++ = k[0];
            *dst = k[1];
        }
    }
    *dst = 0;
    return len >> 1;
}
#endif
