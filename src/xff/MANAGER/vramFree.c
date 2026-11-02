#ifdef NONMATCHING
typedef struct Vram {
    int pad0;
    struct Vram *next;
    int state;
    int flags;
} Vram;

static void func_00030710(Vram *);

void vramFree(Vram *v)
{
    if (v->state == 2 && !(v->flags & 1)) {
        func_00030710(v);
        __asm__ __volatile__("");
    }
}
#endif
