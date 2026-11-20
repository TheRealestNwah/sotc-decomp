typedef int s128 __attribute__((mode(TI)));

/* Vector seen through a union, so copies are TImode accesses in int's alias set. */
typedef union {
    s128 q;
    int v[4];
} Vec;

typedef struct {
    char pad[0x54];
    int *map;
    char pad2[0x90 - 0x58];
} DBGroup;
typedef struct {
    char pad[8];
    DBGroup *groups;
    char pad2[8];
    int unk14;
    char (*verts)[0x40];
} DBData;
typedef struct {
    int layout;
    unsigned int id;
    int n;
    int valid;
} Edge;
typedef struct {
    char pad[8];
    int unk8;
    char pad2[0x14];
    char *unk20;
} LayoutSub;
typedef struct {
    char pad[0x154];
    LayoutSub sub;
    char pad2[0x184 - 0x154 - 0x24];
    char *unk184;
} Layout;
extern Layout *GetLayoutClass(int);
extern void func_000999E0(int *, int, Layout *, int, int);
extern void func_0009AE78(int *, int, char *, int, int, DBGroup *, int, char *);
extern void GetCollisionDBEdgeInfo(Edge *, void *);
extern void glDrawLineStrip(Vec *, int, void *, void *, void *);
extern char UnitMatrix[];
extern int RO_001407D8[];

/* GetCollisionDBEdgeVertexPoint, inlined. */
static inline void EdgeVertexPoint(int *out, Edge *edge)
{
    int buf[4];
    int n = edge->n;
    int sub = edge->id & 0xFFFFFF;
    int grp = (edge->id >> 24) & 0x7F;
    Layout *layout = GetLayoutClass(edge->layout);

    if ((int)edge->id < 0) {
        func_000999E0(buf, 0, layout, grp, sub);
    } else {
        LayoutSub *ls = &layout->sub;
        char *p = ls->unk20;
        DBData *db = *(DBData **)(layout->unk184 + 0x20);
        func_0009AE78(buf, 0, p + 0x28, *(int *)(p + 0x24), ls->unk8, db->groups,
                      db->unk14, db->verts[db->groups[grp].map[sub]]);
    }
    out[0] = buf[n];
    out[1] = buf[RO_001407D8[n]];
}

void DebugDispManualEdgeCollisionDB(void *db, void *a1, void *a2)
{
    Edge edges[3];
    Vec line[2];
    Vec *ptr[2];
    int i;

    GetCollisionDBEdgeInfo(edges, db);
    for (i = 0; i < 3; i++) {
        if (edges[i].valid != 0) {
            EdgeVertexPoint((int *)ptr, &edges[i]);
            line[0].q = ptr[0]->q;
            line[1].q = ptr[1]->q;
            glDrawLineStrip(line, 2, UnitMatrix, a1, a2);
        }
    }
}
