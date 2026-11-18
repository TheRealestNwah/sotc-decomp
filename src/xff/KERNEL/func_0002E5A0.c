typedef struct {
    char pad0[8];
    short *buf;
    char padC[4];
    int size;
    char pad14[4];
    int pos;
    char pad1C[0x1A4 - 0x1C];
    short *buf2;
    int size2;
    int pos2;
} StrmA;

extern void (*B_000E2C68)(int, short *, short *, int);

#ifdef NONMATCHING
/* Parked: 12 words differ (argument setup order before the jalr: the original loads
   the function pointer into $v0 via lui $t0 and computes n * 2 last; gcc computes it
   first and uses $t0 for the pointer). Local, cast, unsigned and fill-option variants
   and a 1,700-iteration permuter run all stay at 12. */
static void func_0002E5A0(StrmA *s, int n)
{
    B_000E2C68(0, s->buf + s->pos, s->buf2 + s->pos2, n * 2);
    s->pos += n;
    s->pos %= s->size;
    s->pos2 += n;
    s->pos2 %= s->size2;
}
#endif
