typedef struct {
    char pad[0xC];
    long *p;
    char pad2[0xC];
    int busy;
} GsCtx;

extern GsCtx *D_00040BF4;
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void iosFTOI4Vector(int *out, float *in);

static __inline__ void GSREG(long reg, long data)
{
    if (D_00040BF4->busy == 0) {
        *D_00040BF4->p++ = data;
        *D_00040BF4->p++ = reg;
    }
}
#define RGBAQ(c) ((long)(c)[0] | ((long)(c)[1] << 8) | ((long)(c)[2] << 16) | ((long)(c)[3] << 24) | ((long)0x3F800000 << 32))
#define XYZ(x, y) (((x) + 0x8000) | ((long)((y) + 0x8000) << 16) | ((long)-1 << 32))


void gsBoxLine(float *rect, int *color, int w)
{
    union { int i[4]; long l[2]; } v;
    long prim, p2;
    register GsCtx *c __asm__("$5");

    gsRegBegin();
    iosFTOI4Vector(v.i, rect);
    c = D_00040BF4;
    if (c->busy == 0) {
        do { *c->p++ = ((long)0x80 << 32) | 0x44; } while (0);
        {
            long r = 0x42;
            __asm__("" : "+r"(r));
            *D_00040BF4->p++ = r;
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
