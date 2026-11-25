typedef struct Child {
    char pad0[0xB4];
    int flag;
    char padB8[0xC8 - 0xB8];
    struct Child *next;
} Child;

typedef struct {
    char pad0[0x1B8];
    unsigned long flags;
    char pad1C0[4];
    int f1C4;
    int f1C8;
    char pad1CC[0x3E4 - 0x1CC];
    Child *child;
} WinObj;

typedef struct {
    char pad0[4];
    WinObj *obj;
} Owner;

typedef struct Node {
    int id;
    char pad4[0x14 - 4];
    Owner *owner;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    char pad0[0x24];
    Node *head;
    Node *tail;
} WinList;

typedef struct {
    char pad0[0x70];
    char group[0x94 - 0x70];
    Node *node;
} Win;

extern WinList D_00139B80;
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern void isysSleepSubThread(void);
extern void RequestDeleteWindowObj(int);

static void func_000D93F0(Win *w)
{
    Node *n = w->node;
    Owner *o = n->owner;
    Child *c;
    int *p;
    int last;
    int cnt;

    if (n->prev)
        n->prev->next = n->next;
    if (n->next)
        n->next->prev = n->prev;
    if (n == D_00139B80.head)
        D_00139B80.head = n->next;
    if (n == D_00139B80.tail)
        D_00139B80.tail = n->prev;
    n->next = 0;
    n->prev = 0;
    if (o) {
        o->obj->flags &= ~0x100;
        o->obj->flags |= 0x200;
        o->obj->f1C8 = 1;
        o->obj->f1C4 = 0;
        for (c = o->obj->child; c; c = c->next)
            c->flag = 0;
    }
    for (;;) {
        cnt = 0;
        last = 0;
        for (p = isysGroupForFirst(w->group, 0); p; p = isysGroupForNext(p, 0)) {
            last = *p;
            cnt++;
        }
        if (last)
            isysGroupForExit(last, 0);
        if (!cnt)
            break;
        isysSleepSubThread();
    }
    RequestDeleteWindowObj(n->id);
}
