#ifdef NONMATCHING /* store scheduling around the jal delay slot */
typedef struct {
    char pad0[0x20];
    int unk20;
    char pad24[0x14];
    float unk38;
    float unk3C;
    char pad40[0x40];
    int unk80;
    char pad84[0x8];
    int unk8C;
    char pad90[0x8];
    float unk98;
} EdgeObj;

typedef struct {
    float v[4];
} EdgeInfo;

extern int GetCollisionDBEdgeInfoNext3(EdgeInfo *, void *);
static int func_0005A078(EdgeObj *, EdgeInfo *, void *, void *, void *, void *, void *);
static void *func_00059EA0(void *, void *);

static inline int detectEdges(EdgeInfo *info, EdgeObj *obj, void *db, void *a2, void *a3, void *t0, void *t1)
{
    EdgeInfo *p;
    int n = GetCollisionDBEdgeInfoNext3(info, db);
    int res = 0;

    p = info;

    while (n-- != 0) {
        res |= func_0005A078(obj, p++, db, a2, a3, t0, t1);
    }
    return res;
}

int charrootdyn_detectCharEdge(EdgeObj *obj, void *db, void *a2, void *a3, void *t0, void *t1, float r)
{
    EdgeInfo info[9];
    void *db2;
    int res;

    obj->unk20 = 0;
    obj->unk98 = obj->unk38 = r;
    obj->unk8C = 0;
    obj->unk3C = r;
    obj->unk80 = 0;
    res = detectEdges(info, obj, db, a2, a3, t0, t1);
    if (res == 0) {
        db2 = func_00059EA0(db, a3);
        if (db2 != 0) {
            res = detectEdges(info, obj, db2, a2, a3, t0, t1);
        }
    }
    return res;
}
#endif
