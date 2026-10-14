typedef struct { int alive; char pad4[8]; int info; char pad10[0x1C]; } Vab;
extern Vab B_000E2200[];

int vab_check_alive(int i)
{
    if (i < 0)
        return 0;
    if (i >= 8)
        return 0;
    return B_000E2200[i].alive != 0;
}
