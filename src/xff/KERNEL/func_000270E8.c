typedef struct {
    int state;
    char pad4[0x3C];
    unsigned char *ptr;
    char pad44[4];
    int status;
} MidiTrk;

extern unsigned char B_000DE110[];
extern int B_000DE210;
extern int B_000DE214;

/* Parked: 39 diffs: registers shift by one; the target reuses the type register for 0x3F */
#ifdef NONMATCHING
static void func_000270E8(MidiTrk *t)
{
    int st = t->status;

    if (st == 0xFF) {
        unsigned char type = *t->ptr++;
        unsigned char len = *t->ptr++;

        if (type == 0x2F) {
            t->ptr = 0;
            t->state = 2;
            if (B_000DE214 != st) {
                B_000DE214 = st;
                B_000DE110[B_000DE210++] = st;
            }
            B_000DE110[B_000DE210++] = 0x3F;
            B_000DE110[B_000DE210++] = len;
        }
    }
}
#else
extern void func_000270E8(MidiTrk *t);
#endif
