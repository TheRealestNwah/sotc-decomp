typedef unsigned long long u64;
typedef struct { u64 qwc:16; u64 pad:10; u64 pce:2; u64 id:3; u64 irq:1; u64 addr:31; u64 spr:1; } DmaTag;
typedef struct { u64 tag; u64 w8; union { DmaTag next; struct { unsigned int nlo, nhi; } w; } u; u64 w18; } Node;
#define nlo u.w.nlo
#define next u.next
typedef struct { u64 tag; u64 t2, t3, t4; unsigned int lo; Node *tail; } Layer;
typedef struct { int a, b; int adrs[2]; char *ptr; int e; int cur; } DlBufs;

extern DlBufs B_00065018;
void iosDlChainTail(int layer, int tag)
{
    volatile DlBufs *dl = &B_00065018;
    int off = layer * 0x30;
    Layer *base = (Layer *)((char *)dl->adrs[dl->cur] + off);
    volatile char *node = dl->ptr;

    dl->ptr = dl->ptr + 0x20;
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(node));
    *(volatile int *)(node + 0x1C) = 0;
    *(volatile u64 *)node = ((u64)tag << 32) | 0x50000000;
    *(volatile int *)(node + 0x18) = 0;
    *(volatile int *)(node + 0xC) = 0;
    *(volatile int *)(node + 8) = 0;
    {
        int a = (*(Node *volatile *)&base->tail)->next.addr;
        __asm__("" : "+r"(a));
        *(volatile u64 *)(node + 0x10) = ((u64)a << 32) | 0x20000000;
    }
    (*(Node *volatile *)&base->tail)->next.addr = (int)node;
    *(int *)&base->tail = (int)node;
}
