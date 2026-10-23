typedef struct Vram {
    int pad0;
    struct Vram *next;
    int state;
    int flags;
} Vram;

typedef struct VramPool {
    char pad[0x4C];
    int f4C;
    char pad50[0xC];
    Vram *list;
    char pad60[4];
    struct VramPool *next;
} VramPool;

extern VramPool *D_00136548;
static void func_00030710(Vram *);
static void func_000305B8(VramPool *, int);

#define PREFETCH(p) __asm__ __volatile__("pref 0, 0x20(%0)" : : "r"(p))

void vramReset(void)
{
    VramPool *pool;
    Vram *v;
    Vram *next;

    for (pool = D_00136548; pool != 0; pool = pool->next) {
        v = pool->list;
        PREFETCH(v);
        while (v != 0) {
            next = v->next;
            if (!(v->flags & 1) && v->state == 2) {
                func_00030710(v);
            }
            v = next;
            PREFETCH(v);
        }
        func_000305B8(pool, pool->f4C);
    }
}
