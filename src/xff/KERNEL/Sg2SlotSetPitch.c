typedef struct {
    int a;
    int b;
    int cur;
    int end;
} SlotLfo;

typedef struct {
    int flags;
    char pad4[0x1C];
    SlotLfo pitch;
    int p30;
    char pad34[0x3C];
    int directPitch;
    char pad74[0x6C];
} Sg2Slot;

extern Sg2Slot B_000DE370[];

#ifdef NONMATCHING
/* Parked: 18 words differ (original keeps redundant slot address copies and uses $s0 for the dead divide) */
static inline void set_lfo(SlotLfo *l, int b, int end, int cur)
{
    int div = 12;
    int q;

    l->b = b;
    l->end = end;
    l->cur = cur;
    q = 3 / div;
}

void Sg2SlotSetPitch(int s, int a, int b, int c, int d, int e)
{
    Sg2Slot *p = &B_000DE370[s];

    set_lfo(&p->pitch, a, b, c);
    p->p30 = d;
    p->directPitch = e;
    p->flags |= 0x80;
}
#endif
