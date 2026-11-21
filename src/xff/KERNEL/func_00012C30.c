typedef unsigned long long u64;
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct {
    u64 tag;
    int w8, wC;
    u64 next;
    int w18, w1C;
    int head, tail;
    char pad28[8];
} Layer;
typedef struct { int bufs[2]; int adrs[2]; int ptr; int max; int cur; } DlBufs;
typedef struct {
    unsigned short nloop:15, eop:1;
    unsigned char pad2[5];
    unsigned char flg:4, nreg:4;
    unsigned char regs0:4, regs1:4;
    unsigned char pad9[7];
} GifTag;
typedef struct {
    GifTag tag;
    u64 data;
    u64 addr;
} Fin;

extern DlBufs B_00065018;
extern volatile Fin fin;

#define dl (&(*(volatile DlBufs *)&B_00065018))
#define LT ((Layer *)(dl->adrs[dl->cur] + dl->max * 0x30))
#define LAYER(o) ((Layer *)((o) + dl->adrs[dl->cur]))

/* Parked: display-list layer reset, 7 words differ. gcc schedules the GIF tag
   clear (por/sq) before the last layer's wC/w1C stores; the Original stores
   them first. */
#ifdef NONMATCHING
void func_00012C30(void)
{
    int i;
    int off;

    for (i = 0; i < dl->max; i++) {
        off = i * 0x30;
        LAYER(off)->w8 = LAYER(off)->wC = LAYER(off)->w18 = LAYER(off)->w1C = 0;
        *(volatile u64 *)&LAYER(off)->tag = 0x10000000;
        { Layer *p = LAYER(off); *(volatile u64 *)&p->next = ((u64)(dl->adrs[dl->cur] + off + 0x30) << 32) | 0x20000000; }
        LAYER(off)->head = LAYER(off)->tail = dl->adrs[dl->cur] + off;
    }
    dl->ptr = dl->bufs[dl->cur];
    *(volatile u64 *)&LT->tag = LT->next = ((u64)(unsigned int)(Fin *)&fin << 32) | 2;
    LT->w8 = LT->w18 = 0;
    LT->wC = LT->w1C = 0x50000002;
    *(volatile u128 *)&fin.tag = 0;
    fin.tag.eop = 1;
    fin.tag.nreg = 1;
    fin.tag.regs0 = 0xE;
    fin.tag.nloop = 1;
    fin.data = 0;
    fin.addr = 0x61;
    LT->head = LT->tail = dl->adrs[dl->cur] + dl->max * 0x30;
}
#endif
