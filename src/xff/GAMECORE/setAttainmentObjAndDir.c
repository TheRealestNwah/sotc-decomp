typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef struct {
    char pad0[0x90];
    int active;
    void *target;
    char link[0xC];
    int linked;
    int unkA8;
    int unkAC;
    Vec4 dir;
    Vec4 prevDir;
    Vec4 offset;
    char padE0[0x330];
    int unk410;
} Attainment;

typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
extern void AddTwoWayLinkNext(void *, void *);
extern char *GetLayoutClass(void *);

void setAttainmentObjAndDir(Attainment *a, void *obj, Vec4 *dir)
{
    if (obj != a->target) {
        a->active = 1;
        if (a->linked != 0) {
            a->linked = 0;
            DeleteTwoWayLink((Link *)(a->link));
        }
        a->target = obj;
        if (obj != 0) {
            AddTwoWayLinkNext(GetLayoutClass(obj) + 0x118, a->link);
            a->linked = 1;
        }
        a->unk410 = 0;
        a->unkA8 = 0;
        a->unkAC = 0;
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&a->offset) : "memory");
    }
    {
        s128 prev = a->dir.q;

        a->unkAC = 0;
        a->unkA8 = 1;
        a->prevDir.q = prev;
    }
    a->dir.q = dir->q;
    a->dir.f[3] = 1.0f;
}
