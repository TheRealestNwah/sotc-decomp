extern void kbGetStatus(void *, void *);
extern void mouseGetStatus(void *);
extern unsigned char B_0014DC14[1];

void usbdevFrameInit(void)
{
    mouseGetStatus(&B_0014DC14);
    kbGetStatus(&B_0014DC14 + 0x5C, &B_0014DC14 + 0x58);
}
