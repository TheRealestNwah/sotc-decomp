typedef struct { float cur, prev, last, step; } Bar;
extern Bar D_0017B050;
extern int D_0017B060;
extern void func_000BC988(int);

void bosslifebar_sethp(float hp)
{
    Bar *b = &D_0017B050;
    if (hp == b->cur)
        return;
    if (hp < b->cur)
        D_0017B060 = 1;
    b->prev = b->last;
    b->cur = hp;
    b->step = 0.1f;
    func_000BC988(3);
}
