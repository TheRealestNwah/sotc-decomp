#ifdef NONMATCHING
/* 23 diffs: gcc narrows the D_00040B40 loads to lbu where the original loads words and reuses the first one for the andi 0xFF; local-int variants were worse (36+). */
extern int iosDlGetWorkBufId(void);
extern char *B_000655D8;
extern int D_00040B40[3];

typedef struct {
    char pad0[0x110];
    unsigned long clear;
    char pad118[0x16C - 0x118];
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    unsigned int flags;
} DispBuf;

void iosSetBGColor(int r, int g, int b)
{
    DispBuf *d;
    int id = iosDlGetWorkBufId();

    d = (DispBuf *)(B_000655D8 + id * 0x190);
    D_00040B40[0] = r;
    D_00040B40[1] = g;
    D_00040B40[2] = b;
    if (d->flags & 1) {
        d->r = D_00040B40[0];
        d->g = D_00040B40[1];
        d->b = D_00040B40[2];
        d->a = 0x80;
        d->clear = (unsigned long)(unsigned char)d->r | ((unsigned long)0xFE00 << 46) | ((unsigned long)d->g << 8) | ((unsigned long)d->b << 16) | ((unsigned long)0x8000 << 16);
    }
}
#endif
