typedef struct {
    char pad0[0x40];
    int ptr;
    char pad44[4];
    unsigned char status;
} MidiTrk;

extern unsigned char B_000DE110[];
extern int B_000DE210;
extern int B_000DE214;

static void func_00026AD0(MidiTrk *t)
{
    register int *pp __asm__("$5") = &t->ptr;
    int *cur;
    int old;
    unsigned char st, a, b, c;
    do {
        cur = &B_000DE214;
        st = t->status;
        a = *(unsigned char *)(*pp)++;
        old = *cur;
        b = *(unsigned char *)(*pp)++;
        c = *(unsigned char *)(*pp)++;
    } while (0);
    if (old != st) {
        *cur = st;
        B_000DE110[B_000DE210++] = st;
    }
    B_000DE110[B_000DE210++] = a;
    B_000DE110[B_000DE210++] = b;
    B_000DE110[B_000DE210++] = c;
}
