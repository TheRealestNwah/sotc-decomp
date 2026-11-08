typedef struct { int sp, base, a, start, end, size, alloc; } Env;
extern int iosMallocAlign(int, int, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern char subThreadGroup[];

#ifdef NONMATCHING
/* Parked: 2 words differ (alloc/base stores swapped) */
int isysInitSubThreadObj(unsigned char *o, int func, int arg, int size)
{
    Env *e;
    int mem;

    switch (o[8]) {
    case 6:
    case 9:
    case 11:
    case 12:
    case 13:
    case 14:
    case 22:
    case 29:
        e = (Env *)(o + 0x20);
        break;
    case 7:
    case 8:
    case 10:
    case 15 ... 21:
    case 23 ... 28:
    case 30 ... 33:
        e = 0;
        break;
    default:
        e = 0;
        break;
    }
    mem = iosMallocAlign(*(int *)o, size, 16);
    e->start = mem;
    if (mem == 0)
        return -1;
    e->end = mem + size;
    e->alloc = 1;
    e->size = size;
    e->sp = func;
    e->base = func;
    isysAddGroupWithLinkParam(o, subThreadGroup, 0, 0);
    return 0;
}
#endif
