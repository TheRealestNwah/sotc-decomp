extern void FlushCache(int mode);
extern int iosDlGetWorkBufId(void);
extern void func_00014BD8(void);

typedef struct { char pad0[8]; unsigned int flags; char padC[0x2C]; } DrawCtx;
typedef struct {
    char pad0[0x10];
    DrawCtx ctx[2];
    char pad80[8];
    char *packet;
    char pad8C[0x14];
    int field;
} GpState;
extern GpState B_00065550;

static inline void send_path3(long addr, long qwc)
{
    int stat;

    do {
        __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(stat));
    } while ((*(volatile int *)0x10009000 & 0x100) || (*(volatile int *)0x1000A000 & 0x100) ||
             (*(volatile int *)0x10003C00 & 0x1F000003) || (stat & 0x100) ||
             (*(volatile int *)0x10003020 & 0xC00));
    *(volatile int *)0x1000A020 = qwc;
    *(volatile int *)0x1000A010 = addr & 0x0FFFFFFF;
    FlushCache(0);
    *(volatile int *)0x1000A000 = 0x141;
}

void iosGsSetDrawContext(void)
{
    GpState *gp = &B_00065550;
    DrawCtx *c = gp->ctx;
    int i;
    char *p;
    long *tag;

    for (i = 0; i < 2; i++, c++) {
        c->flags = (c->flags & ~1) | (gp->field & 1);
        c->flags = (c->flags & ~0x20) | ((gp->field & 1) << 5);
    }
    func_00014BD8();
    p = B_00065550.packet;
    if (iosDlGetWorkBufId() == 0) {
        p += 0x190;
    }
    tag = (long *)(p + 0x10);
    send_path3((unsigned int)tag, (int)(*tag & 0x7FFF) + 1);
}
