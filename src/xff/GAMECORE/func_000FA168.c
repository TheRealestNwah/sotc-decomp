typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
    int i10;
    short s14;
    short s16;
    short s18;
    short s1A;
    int i1C;
} Entry;

static int func_000FA168(char *obj0, int a1, int a2, s128 *src, int t0)
{
    register int ok __asm__("$2") = 0;
    register char *obj __asm__("$10") = obj0;
    register int n __asm__("$4") = *(int *)(obj + 0x380);

    if ((unsigned)n < 0x13) {
        Entry *e;
        if (n < 0x14) {
            register int off __asm__("$2") = n << 5;
            __asm__("" : "+r"(off));
            e = (Entry *)(obj + off + 0x100);
        } else {
            e = 0;
        }
        e->q = *src;
        e->s1A = 1;
        e->s14 = a1;
        e->i1C = a2;
        e->s18 = 0;
        e->s16 = t0;
        e->i10 = 0;
        ok = 1;
        *(int *)(obj + 0x380) = *(int *)(obj + 0x380) + 1;
    }
    return ok;
}
