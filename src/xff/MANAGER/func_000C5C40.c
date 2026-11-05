extern void func_000C0178(char *, char *, int, int, int);
extern void disp_particle_emitter(char *, int, int);

static void func_000C5C40(char **s, int x, int y)
{
    char *p = (char *)(s + 4);

    func_000C0178(p, *(char **)(*s + 0x48), *(int *)(*(char **)(*s + 0x48) + 0xD4), x, y);
    if (*(int *)(p + 0x164) == 1)
        disp_particle_emitter(p, *(int *)(*s + 0x48), *(int *)(*s + 0x4C));
}
