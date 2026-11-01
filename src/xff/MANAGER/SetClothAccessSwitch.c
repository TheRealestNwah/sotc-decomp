extern void *isysGroupForFirst(void *, int);
extern void *isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern int SetLayoutObjAccessSwitch(void *, int);
static inline void applyClothSwitch(char *cloth, int enabled)
{
    int remaining;
    int systemFlag;
    char *instance;
    *(signed char *)(cloth + 8) = enabled;
    remaining = *(short *)(cloth + 4);
    instance = *(char **)cloth;
    systemFlag = *(signed char *)(cloth + 7);
    for (; --remaining != -1; instance += 0x90) {
        int active = 0;
        void *node;
        void *last;
        if (enabled)
            active = *(signed char *)(instance + 0x82) ? systemFlag != 0 : 0;
        node = isysGroupForFirst(instance + 8, 0);
        last = 0;
        for (; node; node = isysGroupForNext(node, 0)) {
            last = *(void **)node;
            SetLayoutObjAccessSwitch(last, active);
        }
        if (last)
            isysGroupForExit(last, 0);
    }
}
void SetClothAccessSwitch(char *cloth, int enabled)
{
    applyClothSwitch(cloth, enabled);
}
