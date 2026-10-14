extern char B_001A5A78[];
extern void *memset(void *, int, unsigned int);

void scrDemoInit(void)
{
    memset(B_001A5A78, 0, 0xB0);
}
