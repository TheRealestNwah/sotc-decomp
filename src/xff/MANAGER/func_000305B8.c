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
    VramBlockList free_list;
    VramBlockList used_list;
} VramPool;

extern VramWork D_00136548;
extern void func_00030440(VramBlock *, VramBlock *);

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

static inline VramBlock *vramNewBlock(VramPool *pool, VramBlockList *list, int state, unsigned int base, int size)
{
    VramBlock *b = D_00136548.free.s.head;
    VramInfo *d;

    vramListRemove(&D_00136548.free, b);
    vramListPush(list, b);
    d = &b->info;
    d->state = state;
    d->attr.b.flag = 0;
    d->attr.w = (d->attr.w & 0x8000FFFF) | (base << 16);
    d->attr.b.size = size;
    d->pool = pool;
    d->block = b;
    d->f10 = 0;
    d->f14 = 0;
    return b;
}

static VramBlock *func_000305B8(VramPool *pool, int size)
{
    VramBlock *res = 0;
    VramBlock *n = pool->free_list.s.head;

    __asm__ __volatile__("pref 0, 0x20(%0)" : : "r"(n));
    while (n != 0) {
        if (n->info.attr.b.size >= size) {
            int st = 2;
            res = vramNewBlock(pool, &pool->used_list, st, n->info.attr.b.base, size);
            func_00030440(res, n);
            break;
        }
        n = n->next;
        __asm__ __volatile__("pref 0, 0x20(%0)" : : "r"(n));
    }
    return res;
}
