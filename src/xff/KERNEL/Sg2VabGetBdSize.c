typedef struct { int unk0; int size; } VabBd;
typedef struct { int alive; char pad4[0x10]; VabBd *bdinfo; char pad18[0x14]; } Vab;
extern Vab B_000E2200[];
extern int vab_check_alive(int id);
int Sg2VabGetBdSize(int id)
{
    Vab *v = &B_000E2200[id];

    int r;
    if (vab_check_alive(id) == 0) {
        return -1;
    }
    r = v->alive;
    if (r != 0) {
        r = B_000E2200[id].bdinfo->size;
    } else {
        r = -1;
    }
    return r;
}
