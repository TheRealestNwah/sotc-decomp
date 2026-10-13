extern void isysInitGroup(void *);
extern unsigned char subThreadGroup[1];

void InitSubThread(void)
{
    isysInitGroup(&subThreadGroup);
}
