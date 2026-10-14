extern int __gameMode;
extern char B_00184890[];
extern void *memset(void *, int, unsigned int);

void gameModeInit(void)
{
    __gameMode = 0;
    memset(B_00184890, 0, 0x20);
}
