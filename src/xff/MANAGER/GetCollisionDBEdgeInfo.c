/* Parked: ~18 diffs, same size. Copies the three edge records (object, packed reference, edge index, edge value) of the collision shape a packed reference points at: masked 15-bit values from a packed shape, or the edge words of a full shape or plane. Precomputing the masks before the second GetLayoutClass call, storing object/key/index in that order and reading the packed edge through a union (so the load is not hoisted above the int stores) brought it from 68 to 18. Remaining diffs are register allocation only: a0/a1 swapped for the cls184/db pointers in the head and the group/offset operands in the packed and full-shape address math. */
#ifdef NONMATCHING
typedef struct Edge {
    int obj;
    unsigned int key;
    int idx;
    int val;
} Edge;

typedef union PackedEdge { int i; unsigned short h[2]; } PackedEdge;

typedef struct Group {
    char pad0[8];
    unsigned char has14;
    char pad9[0xB];
    char *tbl14;
    char pad18[0x3C];
    int *tbl54;
    char pad58[0x38];
} Group;

typedef struct Db {
    char pad0[8];
    Group *groups;
    char padC[0xC];
    char *base18;
} Db;

typedef struct Cls {
    char pad0[0x20];
    Db *db;
} Cls;

typedef struct Layout {
    char pad0[0x184];
    Cls *cls184;
} Layout;

extern Layout *GetLayoutClass(int);

void GetCollisionDBEdgeInfo(Edge *out, Edge *in)
{
    unsigned int k;
    unsigned char b = ((unsigned char *)in)[7];
    Cls *c = GetLayoutClass(in->obj)->cls184;
    Group *g = &c->db->groups[b & 0x7F];

    if (g->has14 != 0) {
        int i;
        PackedEdge *p;
        Edge *o;
        unsigned int hi, lo;
        Db *d;
        k = in->key;
        lo = k & 0xFFFFFF;
        hi = (k >> 24) & 0x7F;
        d = GetLayoutClass(in->obj)->cls184->db;
        p = (PackedEdge *)(d->groups[hi].tbl14 + lo * 0x14 + 8);
        o = out;
        for (i = 0; i < 3; i++) {
            o->obj = in->obj;
            o->key = in->key;
            o->idx = i;
            o->val = p->h[0] & 0x7FFF;
            p++;
            o++;
        }
        return;
    }
    {
        unsigned int key = in->key;
        int s1 = key & 0xFFFFFF;
        int s0 = (key >> 24) & 0x7F;
        Db *d = GetLayoutClass(in->obj)->cls184->db;
        int *p;
        Edge *o;
        int i;

        if ((int)in->key < 0)
            p = (int *)(d->groups[s0].tbl14 + s1 * 0x34 + 0xC);
        else
            p = (int *)(d->base18 + (d->groups[s0].tbl54[s1] << 6) + 0x18);
        o = out;
        for (i = 0; i < 3; i++) {
            o->obj = in->obj;
            o->key = in->key;
            o->idx = i;
            o->val = *p;
            p += 3;
            o++;
        }
    }
}
#else
extern void GetCollisionDBEdgeInfo(void *, void *);
#endif
