/* Parked attempt: 15 words differ (fd and the string base swap $s4/$s5). */
#ifdef NONMATCHING
typedef struct Blk {
    unsigned int size : 24;
    unsigned int o3 : 8;
    unsigned int x4;
    unsigned int next : 24;
    unsigned int p8 : 8;
    unsigned int xC : 24;
    unsigned int used : 1;
    unsigned int sub : 1;
    unsigned int align : 3;
    unsigned int own : 2;
    unsigned int b31 : 1;
    unsigned int x10 : 24;
    unsigned int o0 : 8;
    unsigned int x14 : 24;
    unsigned int o1 : 8;
    unsigned int pc : 24;
    unsigned int o2 : 8;
    struct Blk *nextFree;
    int x20;
    int x24;
} Blk;

typedef struct Ptn {
    unsigned int table : 24;
    unsigned int t3 : 8;
    unsigned short tableNum;
    unsigned short x6;
    unsigned int first : 24;
    unsigned int p8 : 8;
} Ptn;

typedef struct {
    Blk *head;
    int x4;
} FreeTable;

extern void *memset(void *, int, unsigned int);
extern int func_00002F80(int fd, const char *fmt, ...);
extern void *gbPtn;

#define PTR(x) ((void *)((x) << 2))

static void func_00003028(Ptn *ptn, int depth, int flag, int fd)
{
    char indent[depth + 1];
    FreeTable *t;
    Blk *b;
    Blk *p;
    Blk *q;
    int i;
    int n;
    char *name;
    unsigned int u;

    if (depth != 0) {
        memset(indent, ' ', depth);
    }
    indent[depth] = 0;
    func_00002F80(fd, "%s|-Partition %p\n", indent, ptn);
    func_00002F80(fd, "\ttableNum %d\n", ptn->tableNum);
    t = PTR(ptn->table);
    for (i = 0; i < ptn->tableNum; i++, t++) {
        n = 0;
        for (b = t->head; b != 0; b = b->nextFree) {
            func_00002F80(fd, "\t\t%3d:size %d\n", n++, (char *)PTR(b->size));
        }
        func_00002F80(fd, "\t\t%d:FreeNum %d\n", i, n);
    }
    p = PTR(ptn->first);
    q = 0;
    while (p != 0 && (unsigned int)q < (unsigned int)p) {
        q = p;
        if (p->next != 0 && (char *)p + 0x20 + (int)PTR(p->size) != PTR(p->next)) {
            func_00002F80(fd, "XX");
        }
        if (p->used) {
            u = (p->o2 << 18) | p->own;
            u |= (p->o0 << 2) | (p->o1 << 10);
            if (u != 0) {
                name = (char *)u;
            } else {
                name = "";
            }
            func_00002F80(fd, "%s|-USE  %p - %p (%p) size %8.8x pc=%8.8x %s\n", indent, p,
                          (char *)p + 0x20 + (int)PTR(p->size), PTR(p->xC), PTR(p->size), PTR(p->pc), name);
            if (p->sub && ((void *)&p->x24 == gbPtn || flag == 0)) {
                func_00003028((Ptn *)&p->x24, depth + 1, flag, fd);
            }
        } else {
            func_00002F80(fd, "%s|-FREE %p - %p (%p) size %8.8x\n", indent, p, (char *)p + 0x20 + (int)PTR(p->size),
                          PTR(p->xC), PTR(p->size));
        }
        p = PTR(p->next);
    }
}
#endif
