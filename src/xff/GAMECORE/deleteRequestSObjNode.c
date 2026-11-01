typedef struct SNode { int id; char pad[0x54]; struct SNode *next; } SNode;
typedef struct { int a; SNode *head; } SList;
typedef struct { char pad[0x10]; SList list; char pad2[4]; } SGroup;
typedef struct { int n; SGroup grp[20]; char pad[0x238 - 4 - 20 * 0x1C]; SList list; } SReqSet;
extern SReqSet B_0019C250;
extern void func_000B7220(SReqSet *, SList *, SNode *, int);

int deleteRequestSObjNode(int id)
{
    SReqSet *s = &B_0019C250;
    SNode *p;
    int i, j;

    for (i = 0; i < s->n; i++) {
        for (j = 0; j < s->n; j++) {
            SGroup *g = &s->grp[j];
            for (p = g->list.head; p != 0; p = p->next) {
                if (id == p->id) {
                    func_000B7220(s, &g->list, p, j);
                    return 1;
                }
            }
        }
    }
    for (p = s->list.head; p != 0; p = p->next) {
        if (id == p->id) {
            func_000B7220(s, &s->list, p, j);
            return 1;
        }
    }
    return 0;
}
