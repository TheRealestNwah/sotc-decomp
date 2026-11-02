typedef int s128 __attribute__((mode(TI)));

extern void *DldSysUndefSymbol;
extern void func_0003EF60(s128 *, void *, s128 *, void *);

typedef struct {
    int unknown00;
    char pad04[0x1C];
    s128 unknown20;
    int unknown30;
    int unknown34;
} NeckTurn;

static inline void *resourceModuleData(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol)
        return *(void **)(module + 0x10);
    return 0;
}

void doit_neck_turn(NeckTurn *neck, s128 *a, s128 *b, unsigned int *reference)
{
    s128 target[1];
    s128 out;

    if (neck->unknown30) {
        if (neck->unknown34)
            target[0] = *b;
        else
            target[0] = *a;
        func_0003EF60(&out, neck, target, resourceModuleData(reference));
        neck->unknown20 = out;
        if (neck->unknown34 && neck->unknown00 == 0)
            neck->unknown30 = 0;
    }
}
