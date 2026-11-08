typedef struct { int sp, base, a, start, end, size, on; } Env;

extern unsigned char *_isysCreateObj(void *heap, int type, int a, int size, void *del, int b);
extern void isysDeleteSubThread(void);
extern int iosMallocAlign(int heap, int size, int align);
extern int isysAddGroupWithLinkParam(void *obj, void *group, int a, int b);
extern char subThreadGroup[];

static inline int init_env(unsigned char *o, Env *e, int stack, int size)
{
    int p = iosMallocAlign(*(int *)o, size, 16);
    e->start = p;
    if (p == 0) {
        return -1;
    }
    e->on = 1;
    e->size = size;
    e->sp = stack;
    e->base = stack;
    e->end = p + size;
    isysAddGroupWithLinkParam(o, subThreadGroup, 0, 0);
    return 0;
}

unsigned char *isysCreateSubThreadS(int stack, void *heap, int size)
{
    unsigned char *o = _isysCreateObj(heap, 3, 0x40, size + 0x10, isysDeleteSubThread, 4);
    Env *e;
    int err;
    if (o == 0) {
        return 0;
    }
    switch (o[8]) {
    case 6:
    case 9:
    case 11:
    case 12:
    case 13:
    case 14:
    case 22:
    case 29:
    case 33:
        e = (Env *)(o + 0x20);
        break;
    case 7:
    case 8:
    case 10:
    case 15 ... 21:
    case 23 ... 28:
    case 30 ... 32:
        e = 0;
        break;
    default:
        e = 0;
        break;
    }
    err = init_env(o, e, stack, size);
    return err ? 0 : o;
}
