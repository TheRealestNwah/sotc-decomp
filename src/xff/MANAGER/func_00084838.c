typedef struct {
    unsigned int size;
    unsigned int pad4;
    unsigned int next;
    unsigned char padC[3];
    signed char flags;
} MemBlock;

typedef struct {
    int pad0[2];
    unsigned int first;
} Ptn;

#define BLOCK(w) ((MemBlock *)(((w) & 0xFFFFFF) << 2))

extern Ptn rootPtn;
extern Ptn *gbPtn;
extern int mallocStartAdrs;
extern int B_001498F0[];
extern void iosWaitMalloc(void);
extern void iosSignalMalloc(void);

static int func_00084838(int *used, int *base)
{
    MemBlock *b;
    int total = 0;
    int reserved = 0;
    int i;

    *used = 0;
    *base = 0;
    iosWaitMalloc();
    for (b = BLOCK(rootPtn.first); b != 0; b = BLOCK(b->next)) {
        if ((b->flags & 1) && b != ((MemBlock **)gbPtn)[-1]) {
            total += (int)BLOCK(b->size) + 0x20;
        }
    }
    total += mallocStartAdrs;
    *base = total;
    for (b = BLOCK(gbPtn->first); b != 0; b = BLOCK(b->next)) {
        if (b->flags & 1) {
            total += (int)BLOCK(b->size) + 0x20;
        }
    }
    *used = total - *base;
    iosSignalMalloc();
    for (i = 0; i < 14; i++) {
        if (i < 11) {
            reserved += B_001498F0[i];
        }
    }
    return total - reserved;
}
