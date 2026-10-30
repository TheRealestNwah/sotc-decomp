typedef struct {
    char pad0[0x28];
    int originX;
    int originZ;
    char pad30[4];
    int rows;
    int chipW;
    int chipH;
} StageGrid;

typedef struct {
    char pad0[0x308];
    int scriptPriority;
} GlobalVar;

extern StageGrid D_0017A340;
extern GlobalVar gcGlobalVar;
extern char rootPtn[];
extern char D_000246C0[];
extern int *iosMallocAlign(void *, int, int);
extern void createScriptObj(void *, void *, int, int, int, int, int, int);

static void func_0001F838(int x, int z)
{
    StageGrid *g = &D_0017A340;
    int bx = g->originX + x / g->chipW;
    int bz = g->originZ + (g->rows - z / g->chipH);
    int *req = iosMallocAlign(rootPtn, 0x20, 0x10);

    req[0] = bx;
    req[1] = -bz;
    createScriptObj(D_000246C0, req, gcGlobalVar.scriptPriority, 0x1000, 0, 1, 0, 0);
}
