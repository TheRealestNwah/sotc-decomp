typedef struct { char pad[0x8C]; int x8C; int x90; } Cam;
static int func_000EB8D0(Cam *c, int v)
{
    c->x90 = v;
    if (v != 0 || c->x8C != 4) return 1;
    return 0;
}
