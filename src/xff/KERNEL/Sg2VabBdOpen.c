typedef struct { char pad[0xC]; int bd; char pad2[0x1C]; } Vab;
extern Vab B_000E2200[];
extern int vab_check_alive(int id);
int Sg2VabBdOpen(int id, int bd)
{
    Vab *v = &B_000E2200[id];

    if (vab_check_alive(id) == 0) {
        return -1;
    }
    v->bd = bd;
    return 0;
}
