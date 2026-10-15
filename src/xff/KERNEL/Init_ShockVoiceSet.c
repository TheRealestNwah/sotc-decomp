typedef union { unsigned short *p; unsigned short h[2]; } U;
typedef struct { U base; U a; U b; U c; } ShockVoiceSet;

void Init_ShockVoiceSet(ShockVoiceSet *s, unsigned short *base)
{
    s->base.p = base;
    s->c.p = (unsigned short *)((int *)base + base[5]);
    s->a.p = (unsigned short *)((int *)base + base[1]);
    s->b.p = (unsigned short *)((int *)base + base[3]);
}
