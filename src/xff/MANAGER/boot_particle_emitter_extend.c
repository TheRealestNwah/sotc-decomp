static void *func_000C54B0(int);
static int func_000C54B8(void *, int, int, int, int);

int boot_particle_emitter_extend(int on, int a, int b, int c, int d)
{
    int r;
    if (on != 0) {
        r = func_000C54B8(func_000C54B0(on), a, b, c, d);
        if (r == 0)
            r = -1;
        return r;
    }
    return 0;
}
