typedef struct {
    int pad[2];
    int size;
    unsigned char *table;
} VabVelTbl;

typedef struct {
    int rate;
    int depth;
    int table;
} VabLfoTbl;

typedef struct {
    char pad[0x10];
    VabVelTbl vel;
    VabLfoTbl lfo;
} Vab;

extern Vab B_000E2200[];

int vab_get_lfotbl_param(int i, int *rate, int *depth)
{
    int d = B_000E2200[i].lfo.depth;
    int r = B_000E2200[i].lfo.rate;

    *depth = d;
    *rate = r;
    return B_000E2200[i].lfo.table;
}
