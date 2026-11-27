/* Several fields are typed VramNode * so their stores alias the list links,
 * which keeps the Original load/store order. */
typedef struct VramNode VramNode;
typedef struct VramList { VramNode *head; VramNode *count; } VramList;
typedef struct VramPool {
    char pad0[0x54];
    VramList used_list;
    VramList free_list;
} VramPool;
typedef struct VramBlock {
    VramNode *state;
    unsigned int flag : 1;
    unsigned int size : 15;
    unsigned int hi : 16;
    VramNode *pool;
    VramNode *owner;
    VramNode *prev;
    VramNode *next;
} VramBlock;
struct VramNode {
    VramNode *prev;
    VramNode *next;
    VramBlock blk;
};

extern VramList D_00136554;

static inline void listRemove(VramList *l, VramNode *n)
{
    if (l->head == n)
        l->head = n->next;
    if (n->prev)
        n->prev->next = n->next;
    if (n->next)
        n->next->prev = n->prev;
    l->count = (VramNode *)((int)l->count - 1);
}

static inline void listPush(VramList *l, VramNode *n)
{
    if (l->head)
        l->head->prev = n;
    n->prev = 0;
    n->next = l->head;
    l->head = n;
    l->count = (VramNode *)((int)l->count + 1);
}

static inline int blockIsFree(VramBlock *b)
{
    int r;
    if (b != 0)
        r = b->state == (VramNode *)1;
    else
        r = 0;
    return r;
}

static inline void blockUnlink(VramBlock *b)
{
    if (b->prev)
        ((VramBlock *)b->prev)->next = b->next;
    if (b->next)
        ((VramBlock *)b->next)->prev = b->prev;
}

static inline void nodeRelease(VramNode *n, VramPool *pool)
{
    VramList *fl = &D_00136554;
    n->blk.state = 0;
    listRemove(&pool->used_list, n);
    listPush(fl, n);
}

static void func_00030710(VramNode *n)
{
    VramBlock *b = &n->blk;
    VramBlock *next;
    VramBlock *prev;

    b->state = (VramNode *)1;
    {
        VramPool *pool = ((VramPool *)b->pool);
        VramList *from = &pool->free_list;
        VramList *to = &pool->used_list;
        next = (VramBlock *)b->next;
        prev = (VramBlock *)b->prev;
        listRemove(from, n);
        listPush(to, n);
    }
    if (blockIsFree(next)) {
        b->size = b->size + next->size;
        blockUnlink((VramBlock *)b->next);
        nodeRelease(next->owner, ((VramPool *)b->pool));
    }
    if (blockIsFree(prev)) {
        prev->size = prev->size + b->size;
        blockUnlink(b);
        nodeRelease(b->owner, ((VramPool *)b->pool));
    }
}

/* Defined next to its static callee: with func_00030710 in the same file the
 * flags test branches past the duplicate ra restore, as in the Original. The
 * barrier keeps the call from becoming a tail call. */
void vramFree(VramNode *v)
{
    if (v->blk.state == (VramNode *)2) {
        if (!v->blk.flag) {
            func_00030710(v);
            __asm__ __volatile__("");
        }
    }
}
