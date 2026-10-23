typedef struct {
    int pad[2];
    int size;
    unsigned char *table;
} VabVelTbl;

typedef struct {
    char pad[0x10];
    VabVelTbl vel;
    char pad2[0xC];
} Vab;

extern Vab B_000E2200[];

unsigned char *vab_get_veltbl(int i, int *size)
{
    *size = B_000E2200[i].vel.size;
    return B_000E2200[i].vel.table;
}
