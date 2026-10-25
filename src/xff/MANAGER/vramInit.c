typedef struct VramBlock {
    struct VramBlock *prev;
    struct VramBlock *next;
    char pad8[0x18];
} VramBlock;

/* Through a union, the head store keeps the count reload after it. */
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

extern VramWork D_00136548;
extern char rootPtn[];
extern char RO_0013E500[];
extern void *iosMallocAlign(void *, int, int);
extern void memprintf(const char *, ...);

static inline void vramBlockInit(VramBlock *block)
{
    block->next = 0;
    block->prev = 0;
}

static inline void vramListInit(VramBlockList *list)
{
    list->s.head = 0;
    list->s.count = 0;
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

void vramInit(void)
{
    int i;

    D_00136548.pools = 0;
    vramListInit(&D_00136548.free);
    D_00136548.blocks = iosMallocAlign(rootPtn, 0x3000, 4);
    for (i = 0; i < 0x180; i++) {
        vramBlockInit(D_00136548.blocks);
        vramListPush(&D_00136548.free, &D_00136548.blocks[i]);
    }
    memprintf(RO_0013E500);
}
