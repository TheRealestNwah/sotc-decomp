typedef struct {
    unsigned long flags;
    char grp0[8];
    char grp1[8];
} IntrSeg;

typedef struct {
    char pad0[0xC];
    int num;
    IntrSeg *segs;
} IntrSegList;

extern void isysDeleteGroupAllObj(void *grp);

void scriptIntrSegDelete(IntrSegList *l)
{
    IntrSeg *segs;
    IntrSeg *s;
    void *g0;
    void *g1;
    int i;

    segs = l->segs;
    for (i = 0; i < l->num; i++) {
        s = &segs[i];
        g0 = s->grp0;
        g1 = s->grp1;
        if ((int)(s->flags >> 32) & 1) {
            isysDeleteGroupAllObj(g0);
        }
        if ((unsigned int)(s->flags >> 33) & 1) {
            isysDeleteGroupAllObj(g1);
        }
    }
}
