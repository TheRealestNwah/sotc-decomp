typedef struct {
    char pad0[0x40];
    int a;
    int b;
    int c;
} Flags;

static int func_000781E0(Flags *f)
{
    if (f->a || f->b || f->c)
        return 1;
    return 0;
}
