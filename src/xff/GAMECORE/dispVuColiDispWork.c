typedef struct {
    int *entry;
    int pad;
} ColiEntry;
typedef struct {
    int num;
    int max;
    int pad8;
    ColiEntry *list;
    int pad10;
} CollisionFinder;
typedef struct {
    int a;
    int b;
    CollisionFinder finder;
    int enabled;
} VuColiDisp;

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4f;

extern VuColiDisp B_00183B30;
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern char *ptclDisplayListGet(int);
extern void ptclDisplayListPut(int);
extern void dispVuCollisionDB(ColiEntry *, char *);
extern void *memset(void *, int, unsigned int);
extern void iosUnitMatrix(float *);
extern void transMicroCode(int);
extern void ptclmanBegin(void);
extern void ptclmanBuildMatPacket(int, float, float);
extern void ptclmanBuildEnvPacket(void *, float, int, void *, int, int);
extern void ptclmanBuildVtxPacket(char *, int);
extern void ptclmanEnd(void);

void dispVuColiDispWork(void)
{
    CollisionFinder *f;
    int n;
    int cnt;
    int i;
    char *dl;
    char *p;

    if (B_00183B30.enabled == 0)
        return;
    iosDlPushLayer(0x17);
    cnt = 0;
    f = &B_00183B30.finder;
    n = f->num;
    if (f->max < n)
        n = f->max;
    for (i = 0; i < n; i++) {
        if (B_00183B30.finder.list[i].entry != 0)
            cnt++;
    }
    if (cnt > 0) {
        dl = ptclDisplayListGet(cnt);
        if (dl != 0) {
            p = dl;
            for (i = 0; i < n; i++) {
                if (B_00183B30.finder.list[i].entry != 0) {
                    dispVuCollisionDB(&B_00183B30.finder.list[i], p);
                    p += 0x30;
                }
            }
            {
            float v[4] __attribute__((aligned(16)));
            memset(v, 0, 0x10);
            v[3] = 1.0f;
            {
            Vec4f col = {1.0f, 0.6f, 1.2f, 0.5f};
            float mat[4][4] __attribute__((aligned(16)));
            iosUnitMatrix(mat[0]);
            ptclDisplayListPut(cnt);
            transMicroCode(7);
            ptclmanBegin();
            ptclmanBuildMatPacket(2, 1.0f, 1.0f);
            ptclmanBuildEnvPacket(&col, 1.0f, 8, mat, 0, 0);
            ptclmanBuildVtxPacket(dl, cnt);
            ptclmanEnd();
            }
            }
        }
    }
    iosDlPopLayer();
}
