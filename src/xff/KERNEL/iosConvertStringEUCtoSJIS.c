extern int strlen(const char *s);
extern int func_0001C238(int c);

int iosConvertStringEUCtoSJIS(unsigned char *dst, unsigned char *src)
{
    int i = 0;
    int j = 0;
    int len = strlen((char *)src);

    for (; i < len; i++, j++) {
        unsigned char *s = src + i;

        if ((unsigned char)(*s + 0x5F) < 0x5E) {
            unsigned short c;

            i++;
            c = func_0001C238(s[0] | (s[1] << 8));
            dst[j + 1] = c;
            dst[j] = c >> 8;
            j++;
        } else {
            dst[j] = *s;
        }
    }
    dst[len] = 0;
    return len / 2;
}
