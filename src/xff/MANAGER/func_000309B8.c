/* 7 diffs. Takes a free block from D_00136548's free list, pushes it on pool's 0x54 list and fills its info: state 1, attr flag 0, base (pool+0x44) in bits 16-30, size (pool+0x48) in bits 1-15, owner pool, then pool->last = block. The attr word is cleared and filled as flag bitfield / masked word / size bitfield, which gives the Original's -2, 0x8000FFFF, 0xFFFF0001 sequence. The state local (set before the push, found by a 25-minute permuter run) fixes the register allocation. Left: the Original loads pool->size before computing &pool->list (we hoist the addiu to the top) and stores state before block. */
#ifdef NONMATCHING
typedef struct VramInfo {
    int state;
    union {
        struct {
            unsigned int flag : 1;
            unsigned int size : 15;
            unsigned int base : 15;
            unsigned int top : 1;
        } b;
        unsigned int w;
    } attr;
    struct VramPool *pool;
    struct VramBlock *block;
    void *f10;
    void *f14;
} VramInfo;

typedef struct VramBlock {
    struct VramBlock *prev;
    struct VramBlock *next;
    VramInfo info;
} VramBlock;

typedef union VramBlockList {
    struct {
        VramBlock *head;
        int count;
    } s;
} VramBlockList;

typedef struct VramWork {
    void *pools;
    int pad4;
    VramBlock *blocks;
    VramBlockList free;
} VramWork;

typedef struct VramPool {
    char pad0[0x40];
    int mode;
    int base;
    int size;
    int used;
    VramBlock *last;
    VramBlockList used_list;
} VramPool;

extern VramWork D_00136548;

static inline void vramListRemove(VramBlockList *list, VramBlock *block)
{
    if (list->s.head == block) {
        list->s.head = block->next;
    }
    if (block->prev != 0) {
        block->prev->next = block->next;
    }
    if (block->next != 0) {
        block->next->prev = block->prev;
    }
    list->s.count--;
}

static inline void vramListPush(VramBlockList *list, VramBlock *block)
{
    if (list->s.head != 0) {
        list->s.head->prev = block;
    }
    block->prev = 0;
    block->next = list->s.head;
    list->s.head = block;
    list->s.count++;
}

static void func_000309B8(VramPool *pool)
{
    VramBlock *b = D_00136548.free.s.head;
    VramInfo *d = &b->info;
    unsigned int base = (pool->base & 0x7FFF) << 16;
    int size = pool->size;
    int state;

    vramListRemove(&D_00136548.free, b);
    state = 1;
    vramListPush(&pool->used_list, b);
    d->state = state;
    d->attr.b.flag = 0;
    d->attr.w = (d->attr.w & 0x8000FFFF) | base;
    d->attr.b.size = size;
    d->pool = pool;
    d->block = b;
    d->f10 = 0;
    d->f14 = 0;
    pool->last = b;
}
#endif
