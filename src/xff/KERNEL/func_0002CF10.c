/* Parked attempt: 25 words differ. The Original keeps the 64-bit sysex length
 * live in $a2 and counts the copy loop down with a separate truncated int in
 * $a3 (re-truncating len for the pointer advance); gcc here merges the two
 * truncations or keeps a 64-bit counter. Needs --asm-fill-delay-slots (Sg2). */
#ifdef NONMATCHING
typedef struct {
    int state;
    char pad04[0x20 - 0x4];
    int beatDen;
    int beatNum;
    char pad28[0x30 - 0x28];
    double bpm;
    double tpb;
    double tickTime;
    char pad48[0x60 - 0x48];
    unsigned char *ptr;
    char pad64[0x68 - 0x64];
    unsigned char status;
    char pad69[0x78 - 0x69];
    double speed;
} Smfp;

extern unsigned char B_000E11D0[];
extern int B_000E19D0;
extern int B_000E19D4;
extern unsigned int Sg2CtrlGetTickMode(void);

static inline void put(unsigned char *src, long n)
{
    for (; n != 0; n--) {
        B_000E11D0[B_000E19D0++] = *src++;
    }
}

static void func_0002CF10(Smfp *p)
{
    long len;
    int n;
    unsigned char *src;
    unsigned char type;
    unsigned char size;
    unsigned int tempo;
    double t;

    switch (p->status) {
    case 0xF0:
        len = 0;
        do {
            len = (len << 7) + (*p->ptr & 0x7F);
        } while (*p->ptr++ & 0x80);
        B_000E11D0[B_000E19D0++] = 0xF0;
        put(p->ptr, len);
        p->ptr += (int)len;
        break;
    case 0xF7:
        len = 0;
        do {
            len = (len << 7) + (*p->ptr & 0x7F);
        } while (*p->ptr++ & 0x80);
        put(p->ptr, len);
        p->ptr += (int)len;
        break;
    case 0xFF:
        type = *p->ptr++;
        size = *p->ptr++;
        switch (type) {
        case 0x2F:
            p->ptr = 0;
            p->state = 1;
            if (B_000E19D4 != p->status) {
                B_000E19D4 = p->status;
                B_000E11D0[B_000E19D0++] = p->status;
            }
            B_000E11D0[B_000E19D0++] = type;
            B_000E11D0[B_000E19D0++] = size;
            break;
        case 0x51:
            tempo = *p->ptr++ << 16;
            tempo |= *p->ptr++ << 8;
            tempo |= *p->ptr++;
            p->bpm = 60000000.0 / tempo;
            t = 1000000.0 / (60000000.0 / p->bpm) * p->tpb;
            p->tickTime = t / Sg2CtrlGetTickMode();
            p->tickTime = p->tickTime * p->speed / 100.0;
            break;
        case 0x58:
            p->beatNum = *p->ptr++;
            p->beatDen = *p->ptr * *p->ptr;
            p->ptr += 3;
            break;
        default:
            p->ptr += size;
            break;
        }
        break;
    }
}
#endif
