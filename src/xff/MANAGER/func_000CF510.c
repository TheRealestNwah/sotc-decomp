typedef struct {
    float cx;
    float cy;
    float x;
    float y;
    float z;
    int on[3];
    int press[3];
    int dbl[3];
    int release[3];
    float time[3];
    int prev;
} Mouse;

typedef union {
    struct { int pad0; int pad4; int buttons; int dx; int dy; int dz; } s;
    float f[6];
} MouseData;

extern Mouse B_0014DBB8;
extern float D_00137724;
extern int iosGetTCountExtension(void);
extern float iosGetSecondFromTCount(int);

static inline int bit(int v, int m)
{
    return (v & m) != 0;
}

#ifdef NONMATCHING /* 9 diffs: temporaries for the flag bit tests land in v0/v1 swapped */
int func_000CF510(MouseData *d)
{
    Mouse *m = &B_0014DBB8;
    Mouse *m2;
    Mouse *m3;
    float now;
    int o1, o2, o4;
    int n1, n2, n4;
    int d1, d2, d4;
    int r1, r2, r4, p1, p2, p4;

    now = iosGetSecondFromTCount(iosGetTCountExtension());
    D_00137724 = now;
    d1 = 0;
    o4 = bit(m->prev, 4);
    o2 = bit(m->prev, 2);
    o1 = m->prev & 1;
    m->x += (float)d->s.dx;
    m->y += (float)d->s.dy;
    m->z += (float)d->s.dz;
    n2 = bit(d->s.buttons, 2);
    n4 = bit(d->s.buttons, 4);
    n1 = d->s.buttons & 1;
    r1 = o1 ? !n1 : 0;
    r2 = o2 ? !n2 : 0;
    r4 = o4 ? !n4 : 0;
    p1 = o1 ? 0 : n1;
    p2 = o2 ? 0 : n2;
    p4 = o4 ? 0 : n4;
    m->on[0] |= n1;
    m->on[1] |= n2;
    m->on[2] |= n4;
    m->release[0] |= r1;
    m->release[1] |= r2;
    m->release[2] |= r4;
    m->press[0] |= p1;
    m->press[1] |= p2;
    m->press[2] |= p4;
    if (!o1 && n1 && now - m->time[0] < 0.25f)
        d1 = 1;
    m2 = &B_0014DBB8;
    d2 = 0;
    m->dbl[0] |= d1;
    if (!o2 && n2 && D_00137724 - m2->time[1] < 0.25f)
        d2 = 1;
    m3 = &B_0014DBB8;
    d4 = 0;
    m2->dbl[1] |= d2;
    if (!o4 && n4 && D_00137724 - m3->time[2] < 0.25f)
        d4 = 1;
    m3->dbl[2] |= d4;
    if (!B_0014DBB8.dbl[0] && B_0014DBB8.press[0])
        B_0014DBB8.time[0] = D_00137724;
    if (!B_0014DBB8.dbl[1] && B_0014DBB8.press[1])
        B_0014DBB8.time[1] = D_00137724;
    if (!B_0014DBB8.dbl[2] && B_0014DBB8.press[2])
        B_0014DBB8.time[2] = D_00137724;
    B_0014DBB8.prev = d->s.buttons;
    return 1;
}
#endif
