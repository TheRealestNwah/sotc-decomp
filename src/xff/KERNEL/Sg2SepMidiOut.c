typedef struct { int status, previous, unk8, vab, mod; char pad14[60]; } Sep;
extern Sep B_000DD700[];
extern unsigned char B_000DE220[];
extern int B_000DE320;

int Sg2SepMidiOut(unsigned int id, int n, unsigned char *data)
{
    int status;
    int i;
    unsigned char *p;

    if (id < 32) {
        status = B_000DD700[id].status;
        if (status == 0 || status == 2) {
            return -1;
        }
        B_000DE220[B_000DE320++] = B_000DD700[id].mod;
        B_000DE220[B_000DE320++] = n;
        p = data;
        i = n;
        while (i != 0) {
            B_000DE220[B_000DE320++] = *p++;
            i--;
        }
    }
    return 0;
}
