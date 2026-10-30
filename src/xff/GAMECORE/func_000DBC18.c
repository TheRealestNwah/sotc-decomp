typedef struct {
    char pad0[0x10];
    int active;
    char pad14[0x1C];
} Slot;

extern void qsort(void *, unsigned int, unsigned int, int (*)(const void *, const void *));
extern int func_000DBE70(const void *, const void *);

static void func_000DBC18(int *count, int *list, Slot *slots)
{
    int *p = &slots->active;
    int i;

    *count = 0;
    for (i = 0; i < 20; i++, p += 0xC) {
        if (*p == 1) {
            list[*count] = (int)p;
            (*count)++;
        }
    }
    qsort(list, *count, 4, func_000DBE70);
}
