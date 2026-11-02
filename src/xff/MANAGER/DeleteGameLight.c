extern char *GetLightColMan(void);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);

static inline unsigned char *lightClass(unsigned char *o)
{
    switch (o[8]) {
    case 0x1A:
        return o + 0x20;
    default:
        return 0;
    }
}

void DeleteGameLight(unsigned char *target)
{
    unsigned char *last = 0;
    char *man = GetLightColMan();
    void **node;

    for (node = isysGroupForFirst(man + 0x528, 0); node != 0 && (last = *node, 1); node = isysGroupForNext(node, 0)) {
        unsigned char *w = lightClass(last);

        if (w && w == target) {
            char *m = GetLightColMan();

            *(int *)(w + 0x2C) = 0;
            isysAddGroupWithLinkParam(last, m + 0x524, 0, 0);
            _isysDeleteGroup(last, m + 0x528, 0);
            break;
        }
    }
    if (last != 0) {
        isysGroupForExit(last, 0);
    }
    *(int *)(man + 0x52C) |= 2;
}
