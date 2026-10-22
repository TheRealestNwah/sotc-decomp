extern unsigned char gcGlobalVar[];
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);

typedef struct {
    char pad[0x10];
    void (*update)(void *);
} EffectMethods;

void updateSpecialEffectManager(void)
{
    void *last = 0;
    void **entry = isysGroupForFirst(gcGlobalVar + 0x300, 0);
    while (entry != 0) {
        last = *entry;
        (*(EffectMethods **)((char *)last + 0x1C))->update(last);
        entry = isysGroupForNext(entry, 0);
    }
    if (last != 0)
        isysGroupForExit(last, 0);
}
