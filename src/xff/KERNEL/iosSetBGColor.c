extern int iosDlGetWorkBufId(void);
extern char *B_000655D8;
extern volatile int D_00040B40[3];

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
    unsigned long alpha;
    int id = iosDlGetWorkBufId();

    d = (DispBuf *)(B_000655D8 + id * 0x190);
    D_00040B40[0] = r;
    D_00040B40[1] = g;
    D_00040B40[2] = b;
    if (d->flags & 1) {
        alpha = (unsigned long)0x80 << 24;
        d->r = D_00040B40[0];
        d->g = D_00040B40[1];
        d->b = D_00040B40[2];
        d->a = 0x80;
        d->clear = (unsigned long)d->r | ((unsigned long)d->g << 8) | ((unsigned long)d->b << 16) | alpha | ((unsigned long)0x3F800000 << 32);
    }
}
