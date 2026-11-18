extern int LoaderSysPrintf(const char *, ...);
extern void iosDumpDMAStatus(int);
extern void iosDumpVIF1Status(void);
extern void iosDumpGIFStatus(void);
extern void (*D_00040B70)(int);
extern char RO_00043A40[];
extern char RO_00043A78[];
extern char RO_00043AB0[];
extern char RO_00043AE0[];
extern char RO_00043B10[];

#define D1_CHCR (*(volatile int *)0x10009000)
#define D2_CHCR (*(volatile int *)0x1000A000)
#define VIF1_STAT (*(volatile int *)0x10003C00)
#define VIF1_ERR (*(volatile int *)0x10003C30)
#define GIF_STAT (*(volatile int *)0x10003020)

/* VU0 status register vi29; the same local receives every read. */
#define VU_STAT() ({ __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(vu)); vu; })

/* Like libgraph sceGsSyncPath: mode != 0 returns a busy bitmask, mode 0 waits
 * for each path in turn and dumps the hardware state on timeout.
 * msg is pinned to $a0 so the shared printf receives its argument directly. */
int iosSyncPath(int mode, unsigned short timeout)
{
    int cnt;
    int limit;
    int vu;
    register char *msg __asm__("$4");

    limit = timeout ? timeout : 0x2000000;
    cnt = 0;
    if (mode == 0)
        goto wait;
    {
        int r1, r2, r3, r4, d1, d2, vif;
        VU_STAT();
        d1 = D1_CHCR;
        d2 = D2_CHCR;
        vif = VIF1_STAT;
        r1 = (d1 & 0x100) ? 1 : 0;
        r2 = (d2 & 0x100) ? r1 | 2 : r1;
        r3 = (vif & 0x1F000003) ? r2 | 4 : r2;
        r4 = (vu & 0x100) ? r3 | 8 : r3;
        return (GIF_STAT & 0xC00) ? r4 | 0x10 : r4;
    }
err1:
    iosDumpDMAStatus(0);
    iosDumpVIF1Status();
    iosDumpGIFStatus();
    msg = RO_00043A40;
    goto reset;
err2:
    iosDumpDMAStatus(1);
    LoaderSysPrintf(RO_00043A78);
    goto fail;
err3:
    iosDumpDMAStatus(0);
    iosDumpVIF1Status();
    iosDumpGIFStatus();
    msg = RO_00043AB0;
    goto reset;
err4:
    iosDumpDMAStatus(0);
    iosDumpVIF1Status();
    msg = RO_00043AE0;
    goto reset;
err5:
    iosDumpDMAStatus(0);
    iosDumpDMAStatus(1);
    iosDumpVIF1Status();
    iosDumpGIFStatus();
    msg = RO_00043B10;
reset:
    LoaderSysPrintf(msg);
    D_00040B70(VIF1_ERR);
fail:
    return -1;
wait:
    if (D1_CHCR & 0x100)
        do {
            if (++cnt > limit)
                goto err1;
        } while (D1_CHCR & 0x100);
    if (D2_CHCR & 0x100)
        do {
            if (++cnt > limit)
                goto err2;
        } while (D2_CHCR & 0x100);
    if (VIF1_STAT & 0x1F000003)
        do {
            if (++cnt > limit)
                goto err3;
        } while (VIF1_STAT & 0x1F000003);
    if (VU_STAT() & 0x100)
        do {
            if (++cnt > limit)
                goto err4;
        } while (VU_STAT() & 0x100);
    if (GIF_STAT & 0xC00)
        do {
            if (++cnt > limit)
                goto err5;
        } while (GIF_STAT & 0xC00);
    return 0;
}
