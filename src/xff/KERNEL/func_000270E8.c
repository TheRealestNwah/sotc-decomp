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

static void func_000270E8(MidiTrk *t)
{
    int st = t->status;

    if (st == 0xFF) {
        unsigned char type = *t->ptr++;
        unsigned char len = *t->ptr++;

        if (type == 0x2F) {
            t->ptr = 0;
            t->state = 2;
            type = 0x3F;
            if (B_000DE214 != st) {
                B_000DE214 = st;
                B_000DE110[B_000DE210++] = st;
            }
            B_000DE110[B_000DE210++] = type;
            B_000DE110[B_000DE210++] = len;
        }
    }
}
