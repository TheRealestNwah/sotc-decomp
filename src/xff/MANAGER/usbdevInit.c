extern void iosKeybdSetCallBackFunc(void *);
extern void iosMouseSetCallBackFunc(void *);
extern void kbGetStatus(void *, void *);
extern void kbInit();
extern void mouseGetStatus(void *);
extern void mouseInit();
extern unsigned char B_0014DC10[];
extern int func_000D0628(void *status);
extern int func_000D0680(void *status);

void usbdevInit(void)
{
    (*(int *)((char *)(B_0014DC10) + 0)) = 0;
    (*(int *)((char *)(B_0014DC10) + 0x58)) = 0;
    iosMouseSetCallBackFunc(&func_000D0628);
    iosKeybdSetCallBackFunc(&func_000D0680);
    mouseInit();
    kbInit();
    mouseGetStatus(B_0014DC10 + 4);
    kbGetStatus(B_0014DC10 + 0x60, B_0014DC10 + 0x5C);
}
