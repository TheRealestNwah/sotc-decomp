typedef struct GifTag {
    unsigned long nloop : 15;
    unsigned long rest : 49;
} GifTag;

typedef struct GlTag {
    unsigned long dma;
    unsigned int word2;
    unsigned int word3;
    union {
        unsigned long raw;
        GifTag bits;
    } giftag;
} GlTag;

typedef struct GlState {
    char pad0[4];
    unsigned int packet;
    /* The char member lets tag stores alias the pointer, so it is
       reloaded after each store, as in the original. */
    union {
        GlTag *ptr;
        char alias;
    } tag;
    char padC[0x5220 - 0xC];
    int suspended;
} GlState;

extern GlState D_00130480;
extern void iosSetPacketPtrPath1(unsigned int);
extern void iosDlChainTailCurrent(GlTag *);
extern void func_00011AF0(void);
extern void iosDlPopLayer(void);

void glEnd(void)
{
    GlState *gl = &D_00130480;

    if (gl->packet == 0)
        return;
    if (gl->suspended != 0) {
        gl->packet = 0;
        return;
    }
    gl->tag.ptr->giftag.bits.nloop = ((gl->packet - (unsigned int)gl->tag.ptr - 0x10) >> 4) - 1;
    gl->tag.ptr->dma = ((gl->tag.ptr->giftag.raw & 0x7FFF) + 1) | 0x60000000;
    gl->tag.ptr->word2 = 0x10000000;
    gl->tag.ptr->word3 = ((int)gl->tag.ptr->giftag.bits.nloop + 1) | 0x50000000;
    iosSetPacketPtrPath1(gl->packet);
    iosDlChainTailCurrent(gl->tag.ptr);
    gl->packet = 0;
    func_00011AF0();
    iosDlPopLayer();
}
