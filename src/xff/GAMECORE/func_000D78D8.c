typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { char pad[0x10]; Vec4 a; Vec4 b; int c; } D;
typedef struct { char pad[0x10]; Vec4 a; Vec4 b; } S;
static void func_000D78D8(D *dst, char *src)
{
    S *s = (S *)(src + 0x60);
    dst->a.q = s->a.q;
    dst->b.q = s->b.q;
    dst->c = 0;
}
