extern void isysInitGroup(void *);
extern unsigned char B_00065008[1];

void iosInitDC(void)
{
    isysInitGroup(&B_00065008);
}
