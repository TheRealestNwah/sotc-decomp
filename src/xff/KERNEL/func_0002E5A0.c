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

static void func_0002E5A0(StrmA *s, int n)
{
    register void (*f)(int, short *, short *, int) asm("$2") = B_000E2C68;

    f(0, s->buf + s->pos, s->buf2 + s->pos2, n * 2);
    s->pos += n;
    s->pos %= s->size;
    s->pos2 += n;
    s->pos2 %= s->size2;
}
