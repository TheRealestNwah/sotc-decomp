typedef struct {
    char pad[0x28];
    long t28;
    double t30;
    int count;
    unsigned char *base;
    unsigned char *p;
    char flag;
} Seq;

extern unsigned char B_000DE110[];
extern int B_000DE210;
extern int B_000DE214;

#define STATUS(s)                                   \
    if (B_000DE214 != (s)) {                        \
        B_000DE214 = (s);                           \
        B_000DE110[B_000DE210++] = (s);             \
    }

/* Parked: case dispatch order and sysex buffer register use differ. */
#ifdef NONMATCHING
void func_00026B80(Seq *s)
{
    int type, a, b, c, d;
    unsigned char *q;
    unsigned long v;

    type = *s->p++;
    a = *s->p++;
    b = *s->p++;
    c = *s->p++;
    switch (type) {
    case 0xA:
        d = *s->p++;
        STATUS(0xF0);
        q = &B_000DE110[B_000DE210];
        B_000DE210 += 10;
        q[0] = 0;
        q[1] = 0x7E;
        q[2] = 0;
        q[3] = a >> 4;
        q[4] = a & 0xF;
        q[5] = b >> 4;
        q[6] = b & 0xF;
        q[7] = c;
        q[8] = d;
        q[9] = 0xF7;
        break;
    case 0x7:
        d = *s->p++;
        STATUS(0xF0);
        q = &B_000DE110[B_000DE210];
        B_000DE210 += 10;
        q[0] = 0;
        q[1] = 0x7E;
        q[2] = 1;
        q[3] = a >> 4;
        q[4] = a & 0xF;
        q[5] = b >> 4;
        q[6] = b & 0xF;
        q[7] = c;
        q[8] = d;
        q[9] = 0xF7;
        break;
    case 0x41:
        d = *s->p++;
        STATUS(0xF0);
        q = &B_000DE110[B_000DE210];
        B_000DE210 += 10;
        q[0] = 0;
        q[1] = 0x7E;
        q[2] = 2;
        q[3] = a >> 4;
        q[4] = a & 0xF;
        q[5] = b >> 4;
        q[6] = b & 0xF;
        q[7] = c;
        q[8] = d;
        q[9] = 0xF7;
        break;
    case 0x1:
    case 0x2:
        STATUS(0xF0);
        q = &B_000DE110[B_000DE210];
        B_000DE210 += 7;
        q[0] = 0;
        q[1] = 0x7F;
        q[2] = type;
        q[3] = a;
        q[4] = b;
        q[5] = c;
        q[6] = 0xF7;
        break;
    case 0x60:
        if (c != 0) {
            if (s->count == c) {
                s->count = 0;
            } else {
                s->flag = 1;
                v = 0;
                do {
                    v = (v << 7) + (*s->p & 0x7F);
                } while (*s->p++ & 0x80);
                s->t30 = v;
                s->count++;
                s->p = s->base + ((b << 8) | a);
                s->t28 = 0;
            }
        } else {
            s->flag = 1;
            v = 0;
            do {
                v = (v << 7) + (*s->p & 0x7F);
            } while (*s->p++ & 0x80);
            s->t30 = v;
            s->t28 = 0;
            s->p = s->base + ((b << 8) | a);
        }
        break;
    }
}
#endif
