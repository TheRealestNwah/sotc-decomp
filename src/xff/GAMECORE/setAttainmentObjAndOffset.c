typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
    int i[4];
} Vec4;

typedef struct {
    char pad0[0x90];
    int active;
    int target;
    char link[0xC];
    int linked;
    int unkA8;
    int unkAC;
    char padB0[0x20];
    Vec4 offset;
    char padE0[0x330];
    int unk410;
} Attainment;

extern void AddTwoWayLinkNext(void *, void *);
typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
extern char *GetLayoutClass(int);

void setAttainmentObjAndOffset(Attainment *a, int target, Vec4 *offset)
{
    a->active = 1;
    if (a->linked != 0) {
        a->linked = 0;
        DeleteTwoWayLink((Link *)(a->link));
    }
    a->target = target;
    if (target != 0) {
        AddTwoWayLinkNext(GetLayoutClass(target) + 0x118, a->link);
        a->linked = 1;
    }
    a->unk410 = 0;
    a->unkA8 = 0;
    a->unkAC = 0;
    a->offset.q = offset->q;
}
