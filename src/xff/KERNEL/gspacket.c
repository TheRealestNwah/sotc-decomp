typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    u64 *tag;
    u64 *head;
    u64 *data;
    u64 *cur;
    int qwc;
    int size;
    int nloop;
    int err;
} GsPacket;

typedef struct {
    u64 NLOOP : 15;
    u64 EOP : 1;
    u64 pad16 : 16;
    u64 id : 14;
    u64 PRE : 1;
    u64 PRIM : 11;
    u64 FLG : 2;
    u64 NREG : 4;
    u64 REGS0 : 4;
    u64 REGS1 : 4;
    u64 REGS2 : 4;
    u64 REGS3 : 4;
    u64 REGS4 : 4;
    u64 REGS5 : 4;
    u64 REGS6 : 4;
    u64 REGS7 : 4;
    u64 REGS8 : 4;
    u64 REGS9 : 4;
    u64 REGS10 : 4;
    u64 REGS11 : 4;
    u64 REGS12 : 4;
    u64 REGS13 : 4;
    u64 REGS14 : 4;
    u64 REGS15 : 4;
} GifTag;

extern GsPacket *D_00040BF4;
extern u64 *iosGetPacketPtrPath1(void);
extern void iosSetPacketPtrPath1(u64 *);
extern void iosDlChainTailCurrent(void *);
extern void iosFTOI4Vector(int *out, float *in);
/* Original reloads D_00040BF4 after every store: needs -fno-strict-aliasing (config/ee_cflags.json) */

static __inline__ void GSREG(long reg, long data)
{
    if (D_00040BF4->err == 0) {
        *D_00040BF4->cur++ = data;
        *D_00040BF4->cur++ = reg;
    }
}
#define RGBAQ(c) ((long)(c)[0] | ((long)(c)[1] << 8) | ((long)(c)[2] << 16) | ((long)(c)[3] << 24) | ((long)0x3F800000 << 32))
#define XYZ(x, y) (((x) + 0x8000) | ((long)((y) + 0x8000) << 16) | ((long)-1 << 32))

u64 *gsRegBegin(void)
{
    D_00040BF4->err = 0;
    D_00040BF4->cur = iosGetPacketPtrPath1();
    if (D_00040BF4->cur == 0) {
        D_00040BF4->err = 1;
    } else {
        D_00040BF4->tag = D_00040BF4->cur;
        D_00040BF4->cur++;
    }
    if (D_00040BF4->err == 0) {
        D_00040BF4->head = D_00040BF4->cur;
        *D_00040BF4->cur++ = 0;
        if ((int)D_00040BF4->cur & 3)
            *D_00040BF4->cur++ = 0;
        D_00040BF4->data = D_00040BF4->cur;
        D_00040BF4->cur += 2;
    }
    return D_00040BF4->cur;
}

void gsRegEnd(void)
{
    if (D_00040BF4->err == 0) {
        D_00040BF4->size = ((unsigned int)D_00040BF4->cur - (unsigned int)D_00040BF4->data) >> 4;
        D_00040BF4->nloop = D_00040BF4->size - 1;
        if (D_00040BF4->nloop > 0) {
            *(s128 *)D_00040BF4->data = 0;
            ((GifTag *)D_00040BF4->data)->FLG = 0;
            ((GifTag *)D_00040BF4->data)->PRE = 0;
            ((GifTag *)D_00040BF4->data)->EOP = 1;
            ((GifTag *)D_00040BF4->data)->NREG = 1;
            ((GifTag *)D_00040BF4->data)->REGS0 = 0xE;
            ((GifTag *)D_00040BF4->data)->NLOOP = D_00040BF4->nloop;
            ((int *)D_00040BF4->data)[-1] = D_00040BF4->size | 0x50000000;
            ((int *)D_00040BF4->data)[-2] = 0x10000000;
        } else {
            D_00040BF4->cur = D_00040BF4->head;
        }
    }
    if (D_00040BF4->err != 0) {
        D_00040BF4->cur = 0;
        return;
    }
    D_00040BF4->qwc = (((unsigned int)D_00040BF4->cur - (unsigned int)D_00040BF4->tag) >> 4) - 1;
    if (D_00040BF4->qwc > 1) {
        *D_00040BF4->tag = D_00040BF4->qwc | 0x60000000;
        iosSetPacketPtrPath1(D_00040BF4->cur);
        iosDlChainTailCurrent(D_00040BF4->tag);
        D_00040BF4->cur = 0;
        return;
    }
    D_00040BF4->cur = 0;
}

u64 *gsRegEndWithPtr(void)
{
    if (D_00040BF4->err == 0) {
        D_00040BF4->size = ((unsigned int)D_00040BF4->cur - (unsigned int)D_00040BF4->data) >> 4;
        D_00040BF4->nloop = D_00040BF4->size - 1;
        if (D_00040BF4->nloop > 0) {
            *(s128 *)D_00040BF4->data = 0;
            ((GifTag *)D_00040BF4->data)->FLG = 0;
            ((GifTag *)D_00040BF4->data)->PRE = 0;
            ((GifTag *)D_00040BF4->data)->EOP = 1;
            ((GifTag *)D_00040BF4->data)->NREG = 1;
            ((GifTag *)D_00040BF4->data)->REGS0 = 0xE;
            ((GifTag *)D_00040BF4->data)->NLOOP = D_00040BF4->nloop;
            ((int *)D_00040BF4->data)[-1] = D_00040BF4->size | 0x50000000;
            ((int *)D_00040BF4->data)[-2] = 0x10000000;
        } else {
            D_00040BF4->cur = D_00040BF4->head;
        }
    }
    if (D_00040BF4->err != 0) {
        D_00040BF4->cur = 0;
        return 0;
    }
    D_00040BF4->qwc = (((unsigned int)D_00040BF4->cur - (unsigned int)D_00040BF4->tag) >> 4) - 1;
    if (D_00040BF4->qwc > 1) {
        *D_00040BF4->tag = D_00040BF4->qwc | 0x60000000;
        iosSetPacketPtrPath1(D_00040BF4->cur);
        iosDlChainTailCurrent(D_00040BF4->tag);
        D_00040BF4->cur = 0;
        return D_00040BF4->tag;
    }
    D_00040BF4->cur = 0;
    return 0;
}

void gsReglistBegin(void)
{
    D_00040BF4->err = 0;
    D_00040BF4->cur = iosGetPacketPtrPath1();
    if (D_00040BF4->cur == 0) {
        D_00040BF4->err = 1;
    } else {
        D_00040BF4->tag = D_00040BF4->cur;
        D_00040BF4->cur++;
    }
    if (D_00040BF4->err == 0) {
        D_00040BF4->head = D_00040BF4->cur;
        *D_00040BF4->cur++ = 0;
        if ((int)D_00040BF4->cur & 3)
            *D_00040BF4->cur++ = 0;
        D_00040BF4->data = D_00040BF4->cur;
        D_00040BF4->cur += 2;
    }
}

void gsReglistEnd(int prim)
{
    if (D_00040BF4->err == 0) {
        D_00040BF4->size = ((unsigned int)D_00040BF4->cur - (unsigned int)D_00040BF4->data) >> 4;
        D_00040BF4->nloop = (D_00040BF4->size - 1) / 3;
        if (D_00040BF4->nloop > 0) {
            *(s128 *)D_00040BF4->data = 0;
            ((GifTag *)D_00040BF4->data)->FLG = 0;
            ((GifTag *)D_00040BF4->data)->PRE = 1;
            ((GifTag *)D_00040BF4->data)->EOP = 1;
            ((GifTag *)D_00040BF4->data)->NREG = 3;
            ((GifTag *)D_00040BF4->data)->REGS0 = 2;
            ((GifTag *)D_00040BF4->data)->REGS1 = 1;
            ((GifTag *)D_00040BF4->data)->REGS2 = 4;
            ((GifTag *)D_00040BF4->data)->NLOOP = D_00040BF4->nloop * 3;
            ((GifTag *)D_00040BF4->data)->PRIM = prim;
        } else {
            D_00040BF4->cur = D_00040BF4->head;
        }
    }
    if (D_00040BF4->err != 0) {
        D_00040BF4->cur = 0;
        return;
    }
    D_00040BF4->qwc = (((unsigned int)D_00040BF4->cur - (unsigned int)D_00040BF4->tag) >> 4) - 1;
    if (D_00040BF4->qwc > 1) {
        *D_00040BF4->tag = D_00040BF4->qwc | 0x60000000;
        iosSetPacketPtrPath1(D_00040BF4->cur);
        iosDlChainTailCurrent(D_00040BF4->tag);
        D_00040BF4->cur = 0;
        return;
    }
    D_00040BF4->cur = 0;
}

void gsBox(float *rect, int *fill, int *line)
{
    union { int i[4]; long l[2]; } v;

    gsRegBegin();
    iosFTOI4Vector(v.i, rect);
    GSREG(0, 0x4E);
    GSREG(1, RGBAQ(fill));
    GSREG(4, XYZ(v.i[0], v.i[1]));
    GSREG(4, XYZ(v.i[2], v.i[3]));
    GSREG(0, ((line[3] ^ 0x80) == 0) ? 0xCA : 0x4A);
    GSREG(1, RGBAQ(line));
    GSREG(4, XYZ(v.i[0], v.i[1]));
    GSREG(4, XYZ(v.i[0], v.i[3]));
    GSREG(4, XYZ(v.i[2], v.i[3]));
    GSREG(4, XYZ(v.i[2], v.i[1]));
    GSREG(4, XYZ(v.i[0], v.i[1]));
    gsRegEnd();
}

void gsBox2(float *rect, int *fill, int *line, int w)
{
    union { int i[4]; long l[2]; } v;

    gsRegBegin();
    iosFTOI4Vector(v.i, rect);
    GSREG(0, 0x4E);
    GSREG(1, RGBAQ(fill));
    GSREG(4, XYZ(v.i[0], v.i[1]));
    GSREG(4, XYZ(v.i[2], v.i[3]));
    GSREG(0, ((line[3] ^ 0x80) == 0) ? 0xC9 : 0x49);
    GSREG(1, RGBAQ(line));
    GSREG(4, XYZ(v.i[0], v.i[1] - w));
    GSREG(4, XYZ(v.i[0], v.i[3] + w));
    GSREG(4, XYZ(v.i[0] - w, v.i[3]));
    GSREG(4, XYZ(v.i[2] + w, v.i[3]));
    GSREG(4, XYZ(v.i[2], v.i[3] + w));
    GSREG(4, XYZ(v.i[2], v.i[1] - w));
    GSREG(4, XYZ(v.i[2] + w, v.i[1]));
    GSREG(4, XYZ(v.i[0] - w, v.i[1]));
    gsRegEnd();
}

void gsBoxLine(float *rect, int *color, int w)
{
    union { int i[4]; long l[2]; } v;
    long prim, p2;
    register GsPacket *c __asm__("$5");

    gsRegBegin();
    iosFTOI4Vector(v.i, rect);
    c = D_00040BF4;
    if (c->err == 0) {
        do { *c->cur++ = ((long)0x80 << 32) | 0x44; } while (0);
        {
            long r = 0x42;
            __asm__("" : "+r"(r));
            *D_00040BF4->cur++ = r;
        }
        GSREG(0x47, 0x31001);
    }
    prim = (color[3] ^ 0x80) ? 0x49 : 9;
    if (color[3] == 0x80) {
        p2 = prim | 0x80;
    } else {
        p2 = prim;
    }
    GSREG(0, p2);
    GSREG(1, RGBAQ(color));
    GSREG(4, XYZ(v.i[0], v.i[1] - w));
    GSREG(4, XYZ(v.i[0], v.i[3] + w));
    GSREG(4, XYZ(v.i[0] - w, v.i[3]));
    GSREG(4, XYZ(v.i[2] + w, v.i[3]));
    GSREG(4, XYZ(v.i[2], v.i[3] + w));
    GSREG(4, XYZ(v.i[2], v.i[1] - w));
    GSREG(4, XYZ(v.i[2] + w, v.i[1]));
    GSREG(4, XYZ(v.i[0] - w, v.i[1]));
    GSREG(0x47, 0x5164D);
    gsRegEnd();
}
