typedef struct {
    char pad0[0x40];
    int a;
    int b;
} Pair;

static int func_00064D80(int v, Pair *p)
{
    if (v == p->a || v == p->b)
        return 0;
    return 1;
}
