typedef struct {
    char pad0[0x40];
    unsigned char *ptr;
    char pad44[4];
    unsigned char status;
} MidiTrk;

extern unsigned char B_000DE110[];
extern int B_000DE210;
extern int B_000DE214;

/* Parked: 6 words differ (lui/lw scheduling of B_000DE214) */
#ifdef NONMATCHING
static void func_00026AD0(MidiTrk *t)
{
    register unsigned char **pp __asm__("$5") = &t->ptr;
    register int *cur __asm__("$8");
    unsigned char st, a, b, c;
    __asm__("" : "+r"(pp));
    cur = &B_000DE214;
    __asm__("" : "+r"(cur));
    st = t->status;
    a = *(*pp)++;
    b = *(*pp)++;
    c = *(*pp)++;
    if (*cur != st) {
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
