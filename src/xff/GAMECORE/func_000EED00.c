extern void func_000EEEA0(char *, float, char *, float, char *);
extern void func_000EF8C8(char *, float, char *, float, char *);
extern void func_000EFD90(char *, float, char *, float, char *, char *);
extern void func_000F01B8(char *, float, char *, float, char *, char *, int);
extern void func_000F09E8(char *, float, char *, float, char *, char *, int);
extern void func_000F1290(char *, float, char *, float, char *, char *, int);
extern void func_000F1B38(char *, char *, char *, float, float);
extern void func_000F2610(char *, float, char *, float, char *);

static void func_000EED00(char *out, char *a, char *b, int mode, int flags, float wa, float wb)
{
    func_000EEEA0(out + 0x4C, wa, a + 0x4C, wb, b + 0x4C);
    func_000EF8C8(out + 0x1E0, wa, a + 0x1E0, wb, b + 0x1E0);
    func_000EFD90(out + 0x2AC, wa, a + 0x2AC, wb, b + 0x2AC, b + 0x4C);
    func_000F01B8(out + 0x330, wa, a + 0x330, wb, b + 0x330, b + 0x4C, flags);
    func_000F09E8(out + 0x400, wa, a + 0x400, wb, b + 0x400, b + 0x4C, flags);
    func_000F1290(out + 0x4E4, wa, a + 0x4E4, wb, b + 0x4E4, b + 0x4C, flags);
    func_000F1B38(out + 0x5C8, a + 0x5C8, b + 0x5C8, wa, wb);
    if (mode == 1)
        func_000F2610(out + 0x4C, wa, a + 0x4C, wb, b + 0x4C);
}
