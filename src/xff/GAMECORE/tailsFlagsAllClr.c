extern char B_00184138[];
extern void *memset(void *, int, unsigned int);

void tailsFlagsAllClr(void)
{
    memset(B_00184138, 0, 0x320);
}
