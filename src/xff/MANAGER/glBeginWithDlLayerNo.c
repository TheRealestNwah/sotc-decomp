typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct GifTag {
    unsigned long nloop : 15;
    unsigned long eop : 1;
    unsigned long pad16 : 16;
    unsigned long id : 14;
    unsigned long pre : 1;
    unsigned long prim : 11;
    unsigned long flg : 2;
    unsigned long nreg : 4;
    unsigned long regs0 : 4;
    unsigned long regs1 : 60;
} GifTag;

typedef struct GlTag {
    u128 dma;
    union {
        u128 q;
        GifTag bits;
    } giftag;
} GlTag;

typedef struct GlState {
    char pad0[4];
    union {
        unsigned int v;
        char alias;
    } packet;
    union {
        GlTag *ptr;
        char alias;
    } tag;
    int mode;
    int prim;
    int iip;
    int tme;
    int abe;
    int aa1a;
    int aa1b;
    int fge;
    int fst;
    int ctxt;
    int f34;
    int f38;
    char pad3C[0x1B0 - 0x3C];
    union {
        struct {
            unsigned long b0 : 4;
            unsigned long b4 : 1;
        } bits;
        struct {
            int lo;
            int count;
        } w;
    } f1B0;
    int f1B8;
    char pad1BC[0x41F0 - 0x1BC];
    int f41F0;
    char pad41F4[0x5220 - 0x41F4];
    int suspended;
} GlState;

typedef union PK { unsigned long l; char i; } PK;
extern GlState D_00130480;
static const int RO_00116740[8] = { 1, 2, 2, 3, 3, 2, 2, 0 };
static const int RO_00116760[8] = { 0, 1, 2, 3, 3, 4, 5, 6 };
extern void iosDlPushLayer(int);
extern unsigned int iosGetPacketPtrPath1(void);

int glBeginWithDlLayerNo(int mode, int layer)
{
    GlState *gl;
    int aa1 = 0;
    int prim;
    unsigned long *p;

    D_00130480.f41F0 = 0;
    D_00130480.mode = mode;
    iosDlPushLayer(layer);
    switch (mode) {
    case 1:
    case 2:
        aa1 = D_00130480.aa1a;
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        aa1 = D_00130480.aa1b;
        break;
    case 0:
    case 8:
        break;
    default:
        return 1;
    }
    gl = &D_00130480;
    if (gl->packet.v != 0)
        return -1;
    gl->suspended = 0;
    gl->packet.v = iosGetPacketPtrPath1();
    gl->tag.ptr = (GlTag *)gl->packet.v;
    if (gl->packet.v == 0) {
        gl->suspended = 1;
        goto end;
    }
    gl->tag.ptr->giftag.q = 0;
    gl->tag.ptr->giftag.bits.eop = 1;
    gl->tag.ptr->giftag.bits.nreg = 1;
    gl->tag.ptr->giftag.bits.regs0 = 0xE;
    gl->packet.v += 0x20;
    if (mode == 8)
        return 0;
    prim = RO_00116760[mode];
    gl->iip = 1;
    gl->prim = prim;
    gl->f1B8 = 0;
    gl->f1B0.w.count = RO_00116740[prim] - 1;
    gl->f1B0.bits.b4 = 0;
    if (gl->f38 != 0)
        {
            unsigned int *pp = &gl->packet.v;
            PK *q = (PK *)*pp;
            q->l = ((unsigned long)(gl->f34 + 1) << 17) | 0x1164A;
            q++;
            *pp = (unsigned int)(q + 1);
            q->l = gl->ctxt ? 0x48 : 0x47;
        }
    else
        {
            unsigned int *pp = &gl->packet.v;
            PK *q = (PK *)*pp;
            q->l = ((unsigned long)(gl->f34 + 1) << 17) | 0x11001;
            q++;
            *pp = (unsigned int)(q + 1);
            q->l = gl->ctxt ? 0x48 : 0x47;
        }
    {
        GlState *g = &D_00130480;
        unsigned int *pp = &g->packet.v;
        PK *q = (PK *)*pp;
        (q++)->l = (unsigned long)g->prim | ((unsigned long)g->iip << 3) | ((unsigned long)g->tme << 4)
            | ((unsigned long)g->fge << 5) | ((unsigned long)g->abe << 6) | ((unsigned long)aa1 << 7)
            | ((unsigned long)g->fst << 8) | ((unsigned long)g->ctxt << 9);
        *pp = (unsigned int)q;
        q->l = 0;
        *pp = (unsigned int)(q + 1);
    }
end:
    return 0;
}
