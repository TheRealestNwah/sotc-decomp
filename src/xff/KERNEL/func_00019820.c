typedef struct {
    unsigned short first;
    unsigned short last;
} GroupHead;

typedef struct {
    void *obj;
    GroupHead *group;
    char pad8[6];
    unsigned short prev;
    unsigned short next;
    char pad12[6];
} SysGroup;

extern SysGroup B_0006D640[];
extern char RO_00044320[];
extern void iosJumpRecoverPoint(char *);

#define IDX(p) ((p) ? (p) - B_0006D640 : 0)
#define PTR(i) ((i) ? &B_0006D640[i] : 0)

static void func_00019820(SysGroup *at, SysGroup *g, int mode)
{
    GroupHead *h;
    if (at == 0) {
        g->group->first = IDX(g);

        g->group->last = IDX(g);
        g->prev = 0;
        g->next = 0;
        return;
    }
    switch (mode) {
    case 0:
        if ((g->next = at->next) != 0) {
            PTR(at->next)->prev = IDX(g);
        } else {
            at->group->first = IDX(g);
        }
        g->prev = IDX(at);
        at->next = IDX(g);
        break;
    case 1:
        g->next = IDX(at);
        if ((g->prev = at->prev) != 0) {
            PTR(at->prev)->next = IDX(g);
        } else {
            at->group->last = IDX(g);
        }
        at->prev = IDX(g);
        break;
    default:
        iosJumpRecoverPoint(RO_00044320);
        break;
    }
}
