/* Parked: 2 diffs (was 3), same size. Remaining: the state test uses bnel with the ra restore
 * in the likely slot where the Original uses bne (the restore runs on both paths), so the flags
 * test then branches to the ld ra instead of straight to the jr ra. */
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
    if (v->state == 2) {
        if (!(v->flags & 1)) {
            func_00030710(v);
        }
        __asm__ __volatile__("");
    }
}
#endif
