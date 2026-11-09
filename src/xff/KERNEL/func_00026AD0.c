typedef struct {
    char pad0[0x40];
    unsigned char *ptr;
    char pad44[4];
    unsigned char status;
} MidiTrk;

extern unsigned char B_000DE110[];
extern int B_000DE210;
extern int B_000DE214;

/* Parked: 11 diffs: the target loads B_000DE214 after the pointer write-backs */
#ifdef NONMATCHING
static void func_00026AD0(MidiTrk *t)
{
    unsigned char st = t->status;
    unsigned char a = *t->ptr++;
    unsigned char b = *t->ptr++;
    unsigned char c = *t->ptr++;


    if (B_000DE214 != st) {
        B_000DE214 = st;
        B_000DE110[B_000DE210++] = st;
    }
    B_000DE110[B_000DE210++] = a;
    B_000DE110[B_000DE210++] = b;
    B_000DE110[B_000DE210++] = c;
}
#else
extern void func_00026AD0(MidiTrk *t);
#endif
