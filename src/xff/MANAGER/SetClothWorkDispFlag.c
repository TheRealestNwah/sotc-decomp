extern void *isysGroupForFirst(void *, int);
extern void *isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern int SetLayoutObjAccessSwitch(void *, int);
static inline void applyClothDisplay(char *instance, int active)
{
    void *last = 0;
    void *node = isysGroupForFirst(instance + 8, 0);
    for (; node; node = isysGroupForNext(node, 0)) {
        last = *(void **)node;
        SetLayoutObjAccessSwitch(last, active);
    }
    if (last)
        isysGroupForExit(last, 0);
}
void SetClothWorkDispFlag(char *cloth, int index, int enabled)
{
    char *instance = *(char **)cloth + index * 0x90;
    int active = 0;
    *(signed char *)(instance + 0x82) = enabled;
    if (*(signed char *)(cloth + 8))
        active = enabled != 0;
    applyClothDisplay(instance, active);
}
