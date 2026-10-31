typedef struct {
    char pad0[4];
    int count;
    char pad8[0x14 - 8];
    int value;
} Counter;

static void func_00013AF0(int a0, int a1, int a2, int a3, Counter *c)
{
    if (c->value < 99999)
        c->count++;
}
