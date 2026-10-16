typedef struct {
    int a;
    int mouse;
    char pad[0x18];
    int x20;
    int x24;
    int x28;
    int pad2C;
    int x30;
    int x34;
    int x38;
    int x3C;
} WinState;

extern WinState D_00139B80;
extern int B_0014E888[];
extern int usbdevMouseGetStatus(void);
extern void isysInitGroup(void *);

void windowInit(void)
{
    int i;

    D_00139B80.x20 = 0;
    D_00139B80.x24 = 0;
    D_00139B80.x28 = 0;
    D_00139B80.x38 = 0xFF;
    D_00139B80.x34 = 0xFF;
    D_00139B80.x30 = 0xFF;
    D_00139B80.x3C = 0x70;
    D_00139B80.mouse = usbdevMouseGetStatus();
    for (i = 0; i < 2; i++)
        isysInitGroup(&B_0014E888[i]);
}
