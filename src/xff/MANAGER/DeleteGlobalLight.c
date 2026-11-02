extern char *GetLightColMan(void);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);

static inline unsigned char *lightClass(unsigned char *o)
{
    switch (o[8]) {
    case 0x19:
        return o + 0x20;
    default:
        return 0;
    }
}

void DeleteGlobalLight(unsigned char *target)
{
    unsigned char *last = 0;
    char *man = GetLightColMan();
    void **node;

    for (node = isysGroupForFirst(man + 0x51C, 0); node != 0; node = isysGroupForNext(node, 0)) {
        unsigned char *w;

        last = *node;
        w = lightClass(last);
        if (w && target == w) {
            int i;

            *(int *)(w + 0x110) = 0;
            isysAddGroupWithLinkParam(last, man + 0x514, 0, 0);
            _isysDeleteGroup(last, man + 0x51C, 0);
            for (i = 2; i >= 0; i--) {
                *(volatile int *)(w + 0x2C + i * 0x40) = 0;
            }
            break;
        }
    }
    if (last != 0) {
        isysGroupForExit(last, 0);
    }
    *(int *)(man + 0x52C) |= 2;
}
