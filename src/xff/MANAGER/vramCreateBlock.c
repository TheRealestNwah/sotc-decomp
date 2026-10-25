typedef struct VramList {
    void *head;
    int count;
} VramList;

typedef struct VramPool {
    char pad0[0x40];
    int mode;
    int base;
    int size;
    int used;
    char pad50[4];
    VramList used_list;
    VramList free_list;
    struct VramPool *next;
} VramPool;

extern VramPool *D_00136548;
extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
static void func_000309B8(VramPool *);

static inline void vramListInit(VramList *list)
{
    list->head = 0;
    list->count = 0;
}

VramPool *vramCreateBlock(int unused, int type, int base, int size)
{
    VramPool *pool = iosMallocAlign(rootPtn, sizeof(VramPool), 4);

    pool->next = D_00136548;
    D_00136548 = pool;
    switch (type) {
    case 0:
        pool->base = base;
        pool->size = size;
        pool->mode = 0;
        pool->used = 0;
        break;
    case 1:
        pool->base = base;
        pool->size = size;
        pool->mode = 0;
        pool->used = 0;
        break;
    case 2:
        pool->base = base;
        pool->mode = 1;
        pool->size = size;
        pool->used = 0;
        break;
    case 3:
        pool->base = base;
        pool->mode = 2;
        pool->size = size;
        pool->used = 0;
        break;
    case 4:
        pool->base = base;
        pool->mode = 3;
        pool->size = size;
        pool->used = 0;
        break;
    }
    vramListInit(&pool->used_list);
    vramListInit(&pool->free_list);
    func_000309B8(pool);
    return pool;
}
