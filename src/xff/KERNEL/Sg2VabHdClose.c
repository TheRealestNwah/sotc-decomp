typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
    int f28;
} Vab;

extern Vab B_000E2200[];
extern int vab_check_alive(int id);

#ifdef NONMATCHING
/* Parked: 25 words differ (register allocation of the field addresses) */
int Sg2VabHdClose(int id)
{
    if (vab_check_alive(id) == 0) {
        return -1;
    }
    B_000E2200[id].f0 = 0;
    B_000E2200[id].f4 = 0;
    B_000E2200[id].f1C = 0;
    B_000E2200[id].f8 = 0;
    B_000E2200[id].f14 = 0;
    B_000E2200[id].fC = 0;
    B_000E2200[id].f28 = 0;
    B_000E2200[id].f10 = 0;
    B_000E2200[id].f24 = 0;
    B_000E2200[id].f18 = 0;
    B_000E2200[id].f20 = 0;
    return 0;
}
#endif
