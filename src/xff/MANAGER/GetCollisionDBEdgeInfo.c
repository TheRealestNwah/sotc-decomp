/* Parked: same size, only register allocation and scheduling of the group lookup differ (68 words). */
#ifdef NONMATCHING
typedef struct Edge {
    int obj;
    unsigned int key;
    int idx;
    int val;
} Edge;

typedef struct Group {
    char pad0[8];
    unsigned char has14;
    char pad9[0xB];
    char *tbl14;
    char pad18[0x3C];
    int *tbl54;
} Group;

typedef struct Db {
    char pad0[8];
    char *groups;
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
    Group *g = (Group *)(c->db->groups + ((b & 0x7F) * 0x90));

    if (g->has14 != 0) {
        int i;
        unsigned short *p;
        Edge *o;
        unsigned int hi, lo;
        k = in->key;
        hi = k >> 24;
        lo = k & 0xFFFFFF;
        p = (unsigned short *)(((Group *)(GetLayoutClass(in->obj)->cls184->db->groups + ((hi & 0x7F) * 0x90)))->tbl14 + lo * 0x14 + 8);
        o = out;
        i = 0;
        do {
            o->obj = in->obj;
            o->idx = i;
            i++;
            o->key = in->key;
            o->val = *p & 0x7FFF;
            p += 4;
            o++;
        } while (i < 3);
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
            p = (int *)(((Group *)(d->groups + s0 * 0x90))->tbl14 + s1 * 0x34 + 0xC);
        else
            p = (int *)(d->base18 + (((Group *)(d->groups + s0 * 0x90))->tbl54[s1] << 6) + 0x18);
        o = out;
        i = 0;
        do {
            o->obj = in->obj;
            o->idx = i;
            i++;
            o->key = in->key;
            o->val = *p;
            p += 12;
            o++;
        } while (i < 3);
    }
}
#else
extern void GetCollisionDBEdgeInfo(void *, void *);
#endif
