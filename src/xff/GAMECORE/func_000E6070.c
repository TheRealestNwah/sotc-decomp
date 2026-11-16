/* Camera mode dispatch: runs the handler for the current mode (+0x1360) on
   the shared camera state (+0x1370) and that mode's own work area. Modes
   0-7 return their handler's result as tail calls; mode 8's handler is void,
   which keeps it a real call. */
extern int func_000E6EC0(char *, char *, void *);
extern int func_000E70B8(char *, char *, void *);
extern int func_000E82A8(char *, char *, void *);
extern int func_000E85E0(char *, char *, void *);
extern int func_000E88E0(char *, char *, void *);
extern int func_000E8BF8(char *, char *, void *);
extern int func_000E9060(char *, char *, void *);
extern int func_000EA788(char *, char *, void *);
extern void func_000EAAC0(char *, char *, void *);

static int func_000E6070(char *g, void *arg)
{
    char *cam = g + 0x1370;

    switch (*(unsigned int *)(g + 0x1360)) {
    case 0:
        return func_000E6EC0(cam, g + 0x2C40, arg);
    case 1:
        return func_000E70B8(cam, g + 0x2C44, arg);
    case 2:
        return func_000E82A8(cam, g + 0x2D20, arg);
    case 3:
        return func_000E85E0(cam, g + 0x2DE0, arg);
    case 4:
        return func_000E88E0(cam, g + 0x2ED0, arg);
    case 5:
        return func_000E8BF8(cam, g + 0x2FF0, arg);
    case 6:
        return func_000E9060(cam, g + 0x3120, arg);
    case 7:
        return func_000EA788(cam, g + 0x3270, arg);
    case 8:
        func_000EAAC0(cam, g + 0x34E0, arg);
        break;
    }
}
