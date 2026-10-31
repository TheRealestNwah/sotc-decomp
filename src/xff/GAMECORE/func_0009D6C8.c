extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern void *iosMallocAlign(void *, int, int);
extern void createUserPathWork(void *, void *, int, float, float);
extern void setStabilizeYPathWork(void *, int);
extern void setUserPathMode(void *, int);
extern void Kite_InitKitePathWork(void *, void *, float, float);
extern void Kite_SetAnimalID_KitePathWork(void *, int);

typedef struct {
    char p0[0x48];
    float x;
    float z;
} Pos;

typedef struct {
    char p0[0x20];
    Pos *pos;
    char p24[0x278 - 0x24];
    void *path;
    int p27C;
    char kite[4];
    int route;
} Obj;

static void func_0009D6C8(Obj *o)
{
    void *kite = o->kite;
    void *th = isysGetThisSubThread();

    if (o->route >= 0) {
        if (o->path == 0) {
            o->path = iosMallocAlign(rootPtn, 0x3C60, 0x10);
        }
        createUserPathWork(th, o->path, 2, o->pos->x, o->pos->z);
        setStabilizeYPathWork(o->path, 1);
        setUserPathMode(o->path, 1);
    }
    Kite_InitKitePathWork(kite, th, o->pos->x, o->pos->z);
    Kite_SetAnimalID_KitePathWork(kite, 4);
}
