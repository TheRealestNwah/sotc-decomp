extern int D_00139EF0, D_00139EFC, B_001506E4;
extern char B_001506E8[], B_00150728[], B_00150768[];
extern int iosSPrintf(char *, const char *, ...);
extern void nicosysdRebootRequest(void);
extern int iosCreateSema(int, int, int);
int nicosysdInit(void)
{
    if (D_00139EF0) {
        iosSPrintf(B_001506E8, "%s%s", "./nicosysd/NICOSYSD_FIFO-", "-to_boot");
        iosSPrintf(B_00150728, "%s%s", "./nicosysd/NICOSYSD_FIFO-", "-to_server");
        iosSPrintf(B_00150768, "%s%s", "./nicosysd/NICOSYSD_FIFO-", "-to_client");
        nicosysdRebootRequest();
        D_00139EFC = 1;
        return B_001506E4 = iosCreateSema(1, 1, 0);
    }
}
