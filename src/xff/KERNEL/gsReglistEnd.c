typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    u64 *tag;
    u64 *head;
    u64 *data;
    u64 *cur;
    int qwc;
    int size;
    int nloop;
    int err;
} GsPacket;

typedef struct {
    u64 NLOOP : 15;
    u64 EOP : 1;
    u64 pad16 : 16;
    u64 id : 14;
    u64 PRE : 1;
    u64 PRIM : 11;
    u64 FLG : 2;
    u64 NREG : 4;
    u64 REGS0 : 4;
    u64 REGS1 : 4;
    u64 REGS2 : 4;
    u64 REGS3 : 4;
    u64 REGS4 : 4;
    u64 REGS5 : 4;
    u64 REGS6 : 4;
    u64 REGS7 : 4;
    u64 REGS8 : 4;
    u64 REGS9 : 4;
    u64 REGS10 : 4;
    u64 REGS11 : 4;
    u64 REGS12 : 4;
    u64 REGS13 : 4;
    u64 REGS14 : 4;
    u64 REGS15 : 4;
} GifTag;

extern GsPacket *D_00040BF4;
extern void iosSetPacketPtrPath1(u64 *);
extern void iosDlChainTailCurrent(void *);

void gsReglistEnd(int prim)
{
    if (D_00040BF4->err == 0) {
        D_00040BF4->size = ((unsigned int)D_00040BF4->cur - (unsigned int)D_00040BF4->data) >> 4;
        D_00040BF4->nloop = (D_00040BF4->size - 1) / 3;
        if (D_00040BF4->nloop > 0) {
            *(s128 *)D_00040BF4->data = 0;
            ((GifTag *)D_00040BF4->data)->FLG = 0;
            ((GifTag *)D_00040BF4->data)->PRE = 1;
            ((GifTag *)D_00040BF4->data)->EOP = 1;
            ((GifTag *)D_00040BF4->data)->NREG = 3;
            ((GifTag *)D_00040BF4->data)->REGS0 = 2;
            ((GifTag *)D_00040BF4->data)->REGS1 = 1;
            ((GifTag *)D_00040BF4->data)->REGS2 = 4;
            ((GifTag *)D_00040BF4->data)->NLOOP = D_00040BF4->nloop * 3;
            ((GifTag *)D_00040BF4->data)->PRIM = prim;
        } else {
            D_00040BF4->cur = D_00040BF4->head;
        }
    }
    if (D_00040BF4->err != 0) {
        D_00040BF4->cur = 0;
        return;
    }
    D_00040BF4->qwc = (((unsigned int)D_00040BF4->cur - (unsigned int)D_00040BF4->tag) >> 4) - 1;
    if (D_00040BF4->qwc > 1) {
        *D_00040BF4->tag = D_00040BF4->qwc | 0x60000000;
        iosSetPacketPtrPath1(D_00040BF4->cur);
        iosDlChainTailCurrent(D_00040BF4->tag);
        D_00040BF4->cur = 0;
        return;
    }
    D_00040BF4->cur = 0;
}
