typedef struct { int alive; char pad4[8]; int info; char pad10[0x1C]; } Vab;
extern Vab B_000E2200[];

int vab_get_info(int i, int *info, int *alive)
{
    *info = B_000E2200[i].info;
    *alive = B_000E2200[i].alive;
    return 0;
}
