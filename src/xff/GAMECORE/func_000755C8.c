extern int func_00074AC8(unsigned char *, int *, int, int);
extern int func_00074E78(unsigned char *, int *, int, int);
extern void func_000750B8(unsigned char *, int *, int, int);

static int func_000755C8(unsigned char *menu, int *state, int flags, int id)
{
    switch (*state) {
    case 2:
        return func_00074AC8(menu, state, flags, id);
    case 4:
        return func_00074E78(menu, state, flags, id);
    case 5:
        func_000750B8(menu, state, flags, id);
        break;
    }
}
