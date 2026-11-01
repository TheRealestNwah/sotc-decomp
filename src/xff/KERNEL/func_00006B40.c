extern void IosLoadIrxSimulation(void);
extern void initSound(void);
extern void iosMcInit(void);
extern void bootSchedulerThread(void);
extern void iosMouseInit(void);
extern void iosKeybdInit(void);
extern void IosCdvdManagerSimulation(void);
extern void iosDeleteThread(int);

static void func_00006B40(void)
{
    IosLoadIrxSimulation();
    initSound();
    iosMcInit();
    bootSchedulerThread();
    iosMouseInit();
    iosKeybdInit();
    IosCdvdManagerSimulation();
    iosDeleteThread(0);
}
