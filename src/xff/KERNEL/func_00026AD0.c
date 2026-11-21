typedef struct {
    char pad0[0x40];
    unsigned char *ptr;
    char pad44[4];
    unsigned char status;
} MidiTrk;

extern unsigned char B_000DE110[];
extern int B_000DE210;
extern int B_000DE214;

/* Parked: 2 words differ (the lw of B_000DE214 is scheduled one slot early) */
#ifdef NONMATCHING
static void func_00026AD0(MidiTrk *t)
{
    register unsigned char **pp __asm__("$5") = &t->ptr;
    int *cur;
    int old;
    unsigned char st, a, b, c;
    do {
        cur = &B_000DE214;
        st = t->status;
        old = *cur;
        a = *(*pp)++;
        b = *(*pp)++;
        c = *(*pp)++;
    } while (0);
    if (old != st) {
        *cur = st;
        B_000DE110[B_000DE210++] = st;
    }
    B_000DE110[B_000DE210++] = a;
    B_000DE110[B_000DE210++] = b;
    B_000DE110[B_000DE210++] = c;
}
#else
extern void func_00026AD0(MidiTrk *t);
#endif
