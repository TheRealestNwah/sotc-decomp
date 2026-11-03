#ifdef NONMATCHING /* 67 diffs: the original computes the header in both branches and shares the or/store tail; gcc keeps the branches apart */
typedef struct {
    unsigned long tag;
    unsigned int stcycl;
    unsigned int unpack;
} DmaTag;

void modelSetMatrixTransTag(void *unused, DmaTag *p, int count, int usetops)
{
    int n = count >= 0x40 ? 0x3F : count;
    int blocks = (count >> 6) + 1;
    int rest = count - n;
    DmaTag *q = p;
    int i;
    int addr;

    if (usetops) {
        q->unpack = (n << 18) | 0x6C000000;
        q->tag = (blocks + (unsigned long)count * 4) | 0x60000000;
        q->stcycl = 0x01000101;
    } else {
        q->unpack = (n << 18) | 0x6C008000;
        q->tag = (blocks + (unsigned long)count * 4) | 0x60000000;
        q->stcycl = 0x01000101;
    }
    q = (DmaTag *)((char *)p + (n << 6) + 0x10);
    addr = 0xFC;
    for (i = 1; i < blocks; i++) {
        n = rest >= 0x40 ? 0x3F : rest;
        if (usetops)
            q->unpack = addr | (n << 18) | 0x6C000000;
        else
            q->unpack = (n << 18) | 0x6C008000;
        addr += 0xFC;
        rest -= n;
        ((unsigned int *)q)[2] = 0;
        ((unsigned int *)q)[1] = 0;
        ((unsigned int *)q)[0] = 0;
        q = (DmaTag *)((char *)q + (n << 6) + 0x10);
    }
    ((unsigned int *)q)[3] = 0;
    ((unsigned int *)q)[0] = 0;
    ((unsigned int *)q)[1] = 0x14000006;
    ((unsigned int *)q)[2] = 0;
}
#endif
