extern void scrRun(void);
extern void usbdevFrameInit(void);

void func_0000C668(void)
{
    scrRun();
    while (1) {
        usbdevFrameInit();
        scrRun();
    }
}
