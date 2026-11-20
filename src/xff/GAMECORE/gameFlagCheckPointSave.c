typedef struct { int w[0x50 / 4]; } S50;
typedef struct { int w[0x68 / 4]; } S68;
typedef struct { int w[0x190 / 4]; } S190;
typedef struct { int w[0x320 / 4]; } S320;
typedef struct { long w[0x70 / 8]; } S70;
extern S50 B_00183EF0;
extern S68 B_00183F40;
extern S190 B_00183FA8;
extern S320 B_00184138;
extern S320 B_00184458;
extern S70 B_00184778;

static inline void flagClr(int i)
{
    unsigned char *q = (unsigned char *)&B_00183EF0;

    q[i / 8] &= ~(1 << (i & 7));
}

void gameFlagCheckPointSave(S50 *a, S68 *b, S190 *c, S320 *d, S320 *e, S70 *f)
{
    if (a) {
        S50 tmp;
        int i;

        tmp = B_00183EF0;
        for (i = 0x272; i < 0x279; i++)
            flagClr(i);
        *a = B_00183EF0;
        B_00183EF0 = tmp;
    }
    if (b)
        *b = B_00183F40;
    if (c)
        *c = B_00183FA8;
    if (d)
        *d = B_00184138;
    if (e)
        *e = B_00184458;
    if (f)
        *f = B_00184778;
}
