typedef struct {
    char pad0[0x38];
    double d38;
    char pad40[0x60 - 0x40];
    unsigned char *ptr;
} Smf;

static int func_0002B830(Smf *s)
{
    unsigned char *p = s->ptr;
    int len = (p[4] << 24) | (p[5] << 16) | (p[6] << 8) | p[7];
    int format = (p[8] << 8) | p[9];
    int tracks = (p[10] << 8) | p[11];
    int division = (p[12] << 8) | p[13];

    if (len != 6) {
        return -1;
    }
    if (format != 0) {
        return -1;
    }
    if (tracks != 1) {
        return -1;
    }
    s->d38 = division;
    s->ptr = p + 14;
    return 0;
}
