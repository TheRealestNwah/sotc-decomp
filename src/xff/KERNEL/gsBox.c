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
#define XYZ(x, y) (((x) + 0x8000) | (((y) + 0x8000) << 16) | ((long)-1 << 32))

#ifdef NONMATCHING
/* Parked: the original recomputes the 0x8000 bias per block (assembler-expanded addu) and allocates registers differently. */
void gsBox(float *rect, int *fill, int *line)
{
    int v[4];

    gsRegBegin();
    iosFTOI4Vector(v, rect);
    GSREG(0, 0x4E);
    GSREG(1, RGBAQ(fill));
    GSREG(4, XYZ(v[0], v[1]));
    GSREG(4, XYZ(v[2], v[3]));
    GSREG(0, (line[3] ^ 0x80) ? 0x4A : 0xCA);
    GSREG(1, RGBAQ(line));
    GSREG(4, XYZ(v[0], v[1]));
    GSREG(4, XYZ(v[0], v[3]));
    GSREG(4, XYZ(v[2], v[3]));
    GSREG(4, XYZ(v[2], v[1]));
    GSREG(4, XYZ(v[0], v[1]));
    gsRegEnd();
}
#endif
