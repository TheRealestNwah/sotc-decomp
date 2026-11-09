typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    u64 *tag;
    u64 *head;
    u64 *data;
    u64 *cur;
    int size;
    unsigned int n;
    int nm1;
    int err;
} GsPacket;

extern GsPacket *D_00040BF4;
extern void iosSetPacketPtrPath1(u64 *);
extern void iosDlChainTailCurrent(u64 *);
/* Original reloads D_00040BF4 after every store: needs -fno-strict-aliasing (config/ee_cflags.json) */

/* Parked: 19 words off; same tail layout problem as gsRegEnd (bnel with the cur=0 store in the delay slot for size < 2). */
#ifdef NONMATCHING
u64 *gsRegEndWithPtr(void)
{
    if (D_00040BF4->err == 0) {
        D_00040BF4->n = (unsigned int)((char *)D_00040BF4->cur - (char *)D_00040BF4->data) >> 4;
        D_00040BF4->nm1 = D_00040BF4->n - 1;
        if (D_00040BF4->nm1 > 0) {
            *(s128 *)D_00040BF4->data = 0;
            D_00040BF4->data[0] &= 0xF3FFFFFFFFFFFFFFUL;
            D_00040BF4->data[0] &= 0xFFFFBFFFFFFFFFFFUL;
            D_00040BF4->data[0] |= 0x8000;
            D_00040BF4->data[0] = (D_00040BF4->data[0] & 0x0FFFFFFFFFFFFFFFUL) | (0x8000UL << 45);
            D_00040BF4->data[1] = (D_00040BF4->data[1] & ~0xFUL) | 0xE;
            D_00040BF4->data[0] = (D_00040BF4->data[0] & ~0x7FFFUL) | (D_00040BF4->nm1 & 0x7FFF);
            ((int *)D_00040BF4->data)[-1] = D_00040BF4->n | 0x50000000;
            ((int *)D_00040BF4->data)[-2] = 0x10000000;
        } else {
            D_00040BF4->cur = D_00040BF4->head;
        }
    }
    if (D_00040BF4->err != 0) {
        D_00040BF4->cur = 0;
        return 0;
    }
    D_00040BF4->size = ((unsigned int)((char *)D_00040BF4->cur - (char *)D_00040BF4->tag) >> 4) - 1;
    if (D_00040BF4->size < 2) {
        D_00040BF4->cur = 0;
        return 0;
    }
    *D_00040BF4->tag = D_00040BF4->size | 0x60000000;
    iosSetPacketPtrPath1(D_00040BF4->cur);
    iosDlChainTailCurrent(D_00040BF4->tag);
    D_00040BF4->cur = 0;
    return D_00040BF4->tag;
}
#else
extern u64 *gsRegEndWithPtr(void);
#endif
