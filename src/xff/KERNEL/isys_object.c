/*
 * isys object and group lists: deferred object deletion, group links and
 * object creation. Matches only with -fno-strict-aliasing
 * (config/ee_cflags.json).
 */

typedef struct Object {
    int partition;
    int pc;
    union {
        unsigned int word;
        struct {
            unsigned char type;
            unsigned char refs;
            short flags;
        } bytes;
    } header;
    unsigned short groups;
    unsigned short last;
    struct Object *next;
    void (*entry)(struct Object *);
    void (*immediateDelete)(struct Object *);
} Object;

typedef struct {
    unsigned short first;
    unsigned short last;
} GroupHead;

typedef struct {
    Object *obj;
    GroupHead *head;
    int arg;
    unsigned char removed;
    char padD;
    unsigned short next;
    unsigned short prev;
    unsigned short objNext;
    unsigned short objPrev;
    unsigned short freeNext;
} SysGroup;

extern int GetThreadId(void);
extern void SignalSema(int);
extern void WaitSema(int);
extern void iosFree(int);
extern void iosJumpRecoverPoint(char *, ...);
extern int iosCreatePartitionWithPc(int, int, int);
extern void *iosMallocAlign(void *, int, int);

extern int B_000BF6CC;
extern SysGroup *B_000BF6C0;
extern SysGroup *B_000BF6C4;
extern Object *B_000BF6C8;
extern int D_00040D5C;
extern int D_00040D60;
extern SysGroup B_0006D640[];
extern char RO_00044320[];
extern char RO_00044348[];
extern char RO_00044378[];

#define IDX(p) ((p) ? (p) - B_0006D640 : 0)
#define PTR(i) ((i) ? &B_0006D640[i] : 0)

static void func_00019AA8(SysGroup *node);

void isysDeleteObjManager(void)
{
    SysGroup *g;
    SysGroup *nx;
    SysGroup *keep;
    Object *m;
    Object *mn;
    Object *live;
    Object *dead;
    Object *dn;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    keep = 0;
    for (g = B_000BF6C4; g != 0; g = nx) {
        nx = g->freeNext ? &B_0006D640[g->freeNext] : 0;
        if (g->obj->header.bytes.refs == 0) {
            func_00019AA8(g);
        } else {
            g->freeNext = keep ? keep - B_0006D640 : 0;
            keep = g;
        }
    }
    B_000BF6C4 = keep;
    {
        SysGroup *w;
        if (keep != 0) {
            w = keep;
            do {
                w = w->freeNext ? &B_0006D640[w->freeNext] : 0;
            } while (w != 0);
        }
    }
    live = 0;
    dead = 0;
    for (m = B_000BF6C8; m != 0; m = mn) {
        mn = m->next;
        if (!(m->header.word & 0xFFFEFF00)) {
            SysGroup *o;
            for (o = m->groups ? &B_0006D640[m->groups] : 0; o != 0;
                 o = o->objNext ? &B_0006D640[o->objNext] : 0) {
                func_00019AA8(o);
            }
            m->next = dead;
            m->groups = 0;
            dead = m;
        } else {
            m->next = live;
            live = m;
        }
    }
    B_000BF6C8 = live;
    for (m = dead; m != 0; m = dn) {
        dn = m->next;
        if (m->entry != 0) {
            m->entry(m);
        }
        iosFree(m->partition);
    }
    {
        Object *w;
        if (live != 0) {
            w = live;
            do {
                w = w->next;
            } while (w != 0);
        }
    }
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}

static void func_00019820(SysGroup *at, SysGroup *g, int mode)
{
    if (at == 0) {
        g->head->first = IDX(g);

        g->head->last = IDX(g);
        g->next = 0;
        g->prev = 0;
        return;
    }
    switch (mode) {
    case 0:
        if ((g->prev = at->prev) != 0) {
            PTR(at->prev)->next = IDX(g);
        } else {
            at->head->first = IDX(g);
        }
        g->next = IDX(at);
        at->prev = IDX(g);
        break;
    case 1:
        g->prev = IDX(at);
        if ((g->next = at->next) != 0) {
            PTR(at->next)->prev = IDX(g);
        } else {
            at->head->last = IDX(g);
        }
        at->next = IDX(g);
        break;
    default:
        iosJumpRecoverPoint(RO_00044320);
        break;
    }
}

static void func_00019AA8(SysGroup *node)
{
    GroupHead *head = node->head;
    Object *obj = node->obj;

    if (node->next)
        B_0006D640[node->next].prev = node->prev;
    else if (head)
        head->last = node->prev;
    if (node->prev)
        B_0006D640[node->prev].next = node->next;
    else if (head)
        head->first = node->next;
    if (node->objNext)
        B_0006D640[node->objNext].objPrev = node->objPrev;
    else
        obj->last = node->objPrev;
    if (node->objPrev)
        B_0006D640[node->objPrev].objNext = node->objNext;
    else
        obj->groups = node->objNext;
    node->obj = 0;
    node->removed = 0;
    node->next = B_000BF6C0 ? B_000BF6C0 - B_0006D640 : 0;
    B_000BF6C0 = node;
}

int isysAddGroupWithLinkParam(Object *obj, GroupHead *group, int unused, int param)
{
    SysGroup *g;
    SysGroup *p;
    SysGroup *q;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    g = B_000BF6C0;
    if (g != 0) {
        B_000BF6C0 = g->next ? &B_0006D640[g->next] : 0;
    }
    g->arg = param;
    g->obj = obj;
    g->head = group;
    if (group == 0 || obj == 0) {
        iosJumpRecoverPoint(RO_00044348, group, obj);
    }
    {
        GroupHead *h = g->head;
        func_00019820(h->last ? &B_0006D640[h->last] : 0, g, 1);
    }
    q = g;
    if (obj->groups == 0) {
        q->objPrev = 0;
        obj->groups = q ? q - B_0006D640 : 0;
    } else {
        q->objPrev = obj->last;
        p = obj->last ? &B_0006D640[obj->last] : 0;
        p->objNext = q ? q - B_0006D640 : 0;
    }
    q->objNext = 0;
    obj->last = q ? q - B_0006D640 : 0;
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
    return q != 0;
}

int isysAddGroupRelativeWithLinkParam(Object *obj, GroupHead *group, SysGroup *rel, int mode, int unused, int param)
{
    SysGroup *g;
    SysGroup *p;
    SysGroup *q;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    g = B_000BF6C0;
    if (g != 0) {
        B_000BF6C0 = g->next ? &B_0006D640[g->next] : 0;
    }
    g->arg = param;
    g->obj = obj;
    g->head = group;
    if (group == 0 || obj == 0) {
        iosJumpRecoverPoint(RO_00044348, group, obj);
    }
    func_00019820(rel, g, mode);
    q = g;
    if (obj->groups == 0) {
        q->objPrev = 0;
        obj->groups = q ? q - B_0006D640 : 0;
    } else {
        q->objPrev = obj->last;
        p = obj->last ? &B_0006D640[obj->last] : 0;
        p->objNext = q ? q - B_0006D640 : 0;
    }
    q->objNext = 0;
    obj->last = q ? q - B_0006D640 : 0;
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
    return q != 0;
}

void _isysDeleteGroup(Object *obj, GroupHead *group, int noError)
{
    SysGroup *g;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    for (g = obj->groups ? &B_0006D640[obj->groups] : 0; g != 0;
         g = g->objNext ? &B_0006D640[g->objNext] : 0) {
        if (g->head == group) {
            goto found;
        }
    }
    if (noError != 0) {
        goto end;
    }
    iosJumpRecoverPoint(RO_00044378);
found:
    if (g->removed != 1) {
        g->removed = 1;
        g->freeNext = B_000BF6C4 ? B_000BF6C4 - B_0006D640 : 0;
        B_000BF6C4 = g;
    }
end:
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}

void isysDeleteGroupWithLinkParam(Object *obj, GroupHead *group, int param, int noError)
{
    SysGroup *g;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    for (g = obj->groups ? &B_0006D640[obj->groups] : 0; g != 0;
         g = g->objNext ? &B_0006D640[g->objNext] : 0) {
        if (g->head == group && g->arg != 0) {
            goto found;
        }
    }
    if (noError != 0) {
        goto end;
    }
    iosJumpRecoverPoint(RO_00044378);
found:
    if (g->removed != 1) {
        g->removed = 1;
        g->freeNext = B_000BF6C4 ? B_000BF6C4 - B_0006D640 : 0;
        B_000BF6C4 = g;
    }
end:
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}

void isysDeleteGroupAllObj(GroupHead *head)
{
    SysGroup *g;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    g = head->first ? &B_0006D640[head->first] : 0;
    while (g != 0) {
        if (g->removed != 1) {
            g->removed = 1;
            g->freeNext = B_000BF6C4 ? B_000BF6C4 - B_0006D640 : 0;
            B_000BF6C4 = g;
        }
        g->head = 0;
        g = g->next ? &B_0006D640[g->next] : 0;
    }
    head->last = 0;
    head->first = 0;
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}

void isysDeleteAllGroup(Object *obj, int (*filter)(int))
{
    SysGroup *g;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    g = obj->groups ? &B_0006D640[obj->groups] : 0;
    while (g != 0) {
        if ((filter == 0 || filter(g->arg) != 0) && g->removed != 1) {
            g->removed = 1;
            g->freeNext = B_000BF6C4 ? B_000BF6C4 - B_0006D640 : 0;
            B_000BF6C4 = g;
        }
        g = g->objNext ? &B_0006D640[g->objNext] : 0;
    }
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}

SysGroup *isysGroupForFirst(GroupHead *head, int reserved)
{
    SysGroup *g;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    g = head->first ? &B_0006D640[head->first] : 0;
    while (g != 0) {
        if (g->removed == 0 && !(g->obj->header.bytes.flags & 1)) {
            g->obj->header.bytes.refs++;
            break;
        }
        g = g->next ? &B_0006D640[g->next] : 0;
    }
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
    return g;
}

SysGroup *isysGroupForFirstForce(GroupHead *head)
{
    SysGroup *g;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    g = head->first ? &B_0006D640[head->first] : 0;
    if (g != 0)
        g->obj->header.bytes.refs++;
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
    return g;
}

int isysGroupGetObjNumForce(GroupHead *head)
{
    SysGroup *g;
    int count;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    g = head->first ? &B_0006D640[head->first] : 0;
    count = 0;
    while (g != 0) {
        g = g->next ? &B_0006D640[g->next] : 0;
        count++;
    }
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
    return count;
}

void *_isysCreateObj(void *heap, int type, int size, int extra, int entry, int alignment)
{
    /* Preserve the caller PC used to tag the allocation. */
    register void *ra __asm__("$31");
    int pc = (int)ra;
    int partition = iosCreatePartitionWithPc((int)heap, size + extra + 0x24, pc);
    Object *object;
    if (!partition) return 0;
    object = iosMallocAlign((void *)partition, size, alignment);
    if (object) {
        object->header.bytes.type = type;
        object->header.bytes.refs = 0;
        object->partition = partition;
        object->pc = pc;
        object->entry = (void (*)(Object *))entry;
        object->immediateDelete = 0;
        object->last = 0;
        object->groups = 0;
        object->header.word &= 0xFFFF;
    }
    return object;
}

void isysSetObjImmediateDeleteFunc(Object *object, void (*func)(Object *))
{
    object->immediateDelete = func;
}

static inline void unlockObjects(void)
{
    int *p = &D_00040D60;
    if (--*p == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}

static inline void lockObjects(void)
{
    int thread = GetThreadId();
    if (thread == D_00040D5C) {
        D_00040D60++;
        return;
    }
    WaitSema(B_000BF6CC);
    D_00040D5C = thread;
    D_00040D60 = 1;
}

void isysRequestDeleteObj(Object *object)
{
    /* Preserve the caller PC used to tag the deletion request. */
    register void *ra __asm__("$31");
    int pc = (int)ra;
    if (object->immediateDelete) {
        object->immediateDelete(object);
        object->immediateDelete = 0;
    }
    lockObjects();
    object->pc = pc;
    object->header.word |= 0x10000;
    object->next = B_000BF6C8;
    B_000BF6C8 = object;
    unlockObjects();
}

void isysInitGroup(GroupHead *head)
{
    head->last = 0;
    head->first = 0;
}

void isysAddGroupWithLinkParamNoWait(Object *object, GroupHead *group, int unused, int data)
{
    isysAddGroupWithLinkParam(object, group, unused, data);
}
