typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Pos;
typedef struct { float x, y, dx, dy; char pad10[0x10]; int btn[3]; int dbl[3]; } MouseSt;
typedef struct { int f0; MouseSt *st; int f8; int fC; Pos pos; } MouseG;
typedef struct { int f0; int f4; int f8; char padC[0xFE0]; unsigned char ax, ay; } PadM;

extern MouseG D_00139B80;
extern float D_00139BD0;
extern float D_00139BD4;
extern float D_00139BD8;
extern PadM padManagerData;
extern MouseSt *usbdevMouseGetStatus(void);
extern long iosGetTCountExtension(void);
extern float iosGetSecondFromTCount(long);
extern float rintf(float);
extern void mouseDispCursor(void);
extern void mouseSetCursorPosition(float, float);

void windowSetMouseStatus(void)
{
    float now;
    float x;
    float y;
    int d0;
    int d1;
    int d2;
    Pos p;
    MouseSt *st;

    D_00139B80.st = usbdevMouseGetStatus();
    D_00139B80.fC = 0;
    D_00139B80.f8 = 0;
    now = iosGetSecondFromTCount(iosGetTCountExtension());
    D_00139B80.f8 |= padManagerData.f8 & 0x20;
    D_00139B80.fC |= padManagerData.f8 & 0x40;
    st = D_00139B80.st;
    d0 = 0;
    if (st->btn[0] && now - D_00139BD0 < 0.25f)
        d0 = 1;
    st->dbl[0] |= d0;
    st = D_00139B80.st;
    d1 = 0;
    if (st->btn[1] && now - D_00139BD4 < 0.25f)
        d1 = 1;
    st->dbl[1] |= d1;
    st = D_00139B80.st;
    d2 = 0;
    if (st->btn[2] && now - D_00139BD8 < 0.25f)
        d2 = 1;
    st->dbl[2] |= d2;
    if (!D_00139B80.st->dbl[0] && D_00139B80.st->btn[0])
        D_00139BD0 = now;
    if (!D_00139B80.st->dbl[1] && D_00139B80.st->btn[1])
        D_00139BD4 = now;
    if (!D_00139B80.st->dbl[2] && D_00139B80.st->btn[2])
        D_00139BD8 = now;
    if (padManagerData.f0 & 8) {
        x = (padManagerData.ax / 127.5f - 1.0f) * 1.5f;
        y = (padManagerData.ay / 127.5f - 1.0f) * 1.5f;
        x = x < 0.0f ? x * -x : x * x;
        x = x < 0.0f ? x * -x : x * x;
        y = y < 0.0f ? y * -y : y * y;
        y = y < 0.0f ? y * -y : y * y;
        x = rintf(x);
        y = rintf(y);
        D_00139B80.st->dx += x;
        D_00139B80.st->dy += y;
        D_00139B80.st->x += x;
        D_00139B80.st->y += y;
        if (x != 0.0f || y != 0.0f)
            mouseDispCursor();
    }
    p.f[0] = D_00139B80.st->x;
    p.f[1] = D_00139B80.st->y;
    D_00139B80.pos.q = p.q;
    mouseSetCursorPosition(p.f[0], p.f[1]);
    D_00139B80.st->x = p.f[0];
    D_00139B80.st->y = p.f[1];
}
