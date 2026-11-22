/* Removes every emitter node whose key matches from a linked list, releasing the emitter (callback, work list) and freeing the node. */
typedef union GWork {
    struct {
        char pad0[0xA8];
        union GWork *next;
    } s;
} GWork;

typedef struct GWorkList {
    int num;
    GWork *head;
    GWork *tail;
} GWorkList;

typedef struct Emitter {
    char pad0[0x114];
    int active;
    char pad118[0x124 - 0x118];
    GWorkList works;
    char pad130[0x158 - 0x130];
    int state;
    void (*callback)(int);
    int callbackArg;
    char pad164[0x170 - 0x164];
    char finder[1];
} Emitter;

typedef struct EmitterNode {
    char pad0[0x10];
    Emitter emitter;
    char pad[0x1B0 - 0x10 - sizeof(Emitter)];
    struct EmitterNode *next;
} EmitterNode;

extern GWorkList B_001499B0;
extern int CheckCollisionFinderAlive(void *);
extern void ReleaseCollisionFinder(void *);
extern void iosFree(void *);

static inline int particleGWorkRemove(GWorkList *list, GWork *work)
{
    GWork *prev;
    GWork *cur;
    GWork *head;

    head = list->head;
    if (head != 0) {
        cur = head;
        prev = 0;
        do {
            if (cur == work) {
                if (prev != 0) {
                    prev->s.next = work->s.next;
                }
                if (list->head == work) {
                    list->head = work->s.next;
                }
                if (list->tail == work) {
                    list->tail = prev;
                }
                list->num--;
                return 1;
            }
            prev = cur;
            cur = cur->s.next;
        } while (cur != 0);
    }
    return 0;
}

static inline void particleGWorkAppend(GWorkList *list, GWork *work)
{
    if (work == 0) {
        return;
    }
    if (list->tail != 0) {
        list->tail->s.next = work;
    } else {
        list->head = work;
    }
    work->s.next = 0;
    list->tail = work;
    list->num++;
}

static inline void releaseEmitter(Emitter *e, int one)
{
    GWork *work;
    GWorkList *works;

    if (e == 0) {
        return;
    }
    e->active = one;
    if (e->state == one && e->callback != 0) {
        e->callback(e->callbackArg);
    }
    works = &e->works;
    while (works->head != 0) {
        work = works->head;
        particleGWorkRemove(works, work);
        particleGWorkAppend(&B_001499B0, work);
    }
    if (CheckCollisionFinderAlive(e->finder)) {
        ReleaseCollisionFinder(e->finder);
    }
}

static inline void removeNode(EmitterNode **list, EmitterNode **pp, EmitterNode *prev, int one)
{
    if (prev != 0) {
        prev->next = (*pp)->next;
    } else {
        *list = (*pp)->next;
    }
    releaseEmitter(&(*pp)->emitter, one);
    iosFree(*pp);
    *pp = prev;
}

static void func_000BF688(EmitterNode **list, int key)
{
    EmitterNode *prev;
    EmitterNode *cur;
    int one;

    prev = 0;
    cur = *list;
    if (cur != 0) {
        one = 1;
        do {
            EmitterNode *c = cur;
            if (*(int *)c == key) {
                removeNode(list, &cur, prev, one);
                c = cur;
            }
            if (c == 0) {
                prev = 0;
                c = *list;
                cur = c;
            } else {
                prev = c;
                c = c->next;
                cur = c;
            }
        } while (cur != 0);
    }
}
