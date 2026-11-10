#ifdef NONMATCHING
/* Parked: 17 diffs. Volatile local arrays reproduce the repeated reloads; left are the
 * load order of the D_00040B78/D_00040B80 arguments and a v0/v1 swap in the == 2 test. */
extern char *D_00040B78[];
extern char *D_00040B80[];
extern char *D_00040B90[];
extern char RO_00043058[], RO_00043098[], RO_000430C0[], RO_00043108[], RO_00043168[], RO_00043190[],
    RO_000431B0[], RO_000431D8[], RO_00043210[], RO_00043248[], RO_00043268[], RO_00043290[];
extern void LoaderSysPrintf(const char *, ...);

void iosDumpDMAStatus(int ch)
{
    volatile unsigned int chcr[2] = { *(volatile unsigned int *)0x10009000, *(volatile unsigned int *)0x1000A000 };
    volatile unsigned int madr[2] = { *(volatile unsigned int *)0x10009010, *(volatile unsigned int *)0x1000A010 };
    volatile unsigned int tadr[2] = { *(volatile unsigned int *)0x10009030, *(volatile unsigned int *)0x1000A030 };
    volatile unsigned int asr0[2] = { *(volatile unsigned int *)0x10009040, *(volatile unsigned int *)0x1000A040 };
    volatile unsigned int asr1[2] = { *(volatile unsigned int *)0x10009050, *(volatile unsigned int *)0x1000A050 };
    volatile unsigned int qwc[2] = { *(volatile unsigned int *)0x10009020, *(volatile unsigned int *)0x1000A020 };

    LoaderSysPrintf(RO_00043058, ch + 1);
    LoaderSysPrintf(RO_00043098);
    LoaderSysPrintf(RO_000430C0, D_00040B78[chcr[ch] & 1], D_00040B80[(chcr[ch] >> 2) & 3], (chcr[ch] >> 4) & 3);
    LoaderSysPrintf(RO_00043108, D_00040B90[(chcr[ch] >> 6) & 1], D_00040B90[(chcr[ch] >> 7) & 1], (chcr[ch] >> 8) & 1, chcr[ch] >> 16);
    LoaderSysPrintf(RO_00043168);
    LoaderSysPrintf(RO_00043190, madr[ch] & 0x7FFFFFFF);
    LoaderSysPrintf(RO_000431B0);
    LoaderSysPrintf(RO_00043190, tadr[ch] & 0x7FFFFFFF);
    if ((chcr[ch] >> 4) & 3) {
        LoaderSysPrintf(RO_000431D8);
        if (((chcr[ch] >> 4) & 3) == 2) {
            LoaderSysPrintf(RO_00043210, asr0[ch] & 0x7FFFFFFF, asr1[ch] & 0x7FFFFFFF);
        } else {
            LoaderSysPrintf(RO_00043248, asr0[ch] & 0x7FFFFFFF);
        }
    }
    LoaderSysPrintf(RO_00043268);
    LoaderSysPrintf(RO_00043290, qwc[ch], qwc[ch] * 16);
}
#endif
