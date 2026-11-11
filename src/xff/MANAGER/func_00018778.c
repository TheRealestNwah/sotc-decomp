/* Parked draft: builds a two-buffer GIF display list for a 32-segment unit circle fan
   (cos, sin, 0, 1 quadwords). Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef long s64;

extern char rootPtn[];
extern void *iosMallocAlign(char *, int, int);
extern float iosGetCosf(float);
extern float iosGetSinf(float);

typedef struct Packet {
    int tag0;
    int pad4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    s64 f20;
    int f28;
    char pad2C[4];
    int f30;
    int f34;
    int f38;
    int f3C;
    s64 f40;
    s64 f48;
} Packet;

static void *func_00018778(s64 arg)
{
    char *list = iosMallocAlign(rootPtn, 0x500, 0x10);
    int *hdr = (int *)list;
    Packet **slot;
    int buf;

    hdr[0] = 6;
    hdr[2] = (int)(list + 0x20);
    hdr[3] = (int)(list + 0x290);
    hdr[1] = 0;
    slot = (Packet **)(list + 8);
    for (buf = 0; buf < 2; buf++) {
        Packet *p = *slot;
        s64 flags;
        s128 *q;
        int i;

        p->f18 = 0x01000101;
        p->f1C = 0x6C0103A0;
        p->tag0 = 0x60000026;
        p->f8 = 0x10000000;
        p->fC = 0;
        p->f10 = 0;
        p->f14 = 0;
        flags = ((arg << 7) | (arg == 0 ? 0x42 : 2)) << 0x2F;
        p->f20 = flags | ((0x10004000L << 0x20) | 0x8002);
        p->f3C = 0x6C228000;
        p->f40 = flags | ((0x10004000L << 0x20) | 0x8021);
        q = (s128 *)((char *)p + 0x50);
        p->f28 = 4;
        p->f30 = 0x10000000;
        p->f34 = 0;
        p->f38 = 0;
        p->f48 = (0xDFL << 0x20) | 4;
        for (i = 0; i <= 0x20; i++) {
            float ang = (float)i * 6.283185f * 0.03125f;
            float v[4];
            v[0] = iosGetCosf(ang);
            v[1] = iosGetSinf(ang);
            v[2] = 0;
            v[3] = 1.0f;
            *q++ = *(s128 *)v;
        }
        ((int *)q)[0] = 0x14000012;
        ((int *)q)[1] = 0;
        ((int *)q)[2] = 0;
        ((int *)q)[3] = 0x10000000;
        slot += 1;
    }
    return list;
}
#endif
