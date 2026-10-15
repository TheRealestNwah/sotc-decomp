extern void isysInitGroup(void *);
extern unsigned char subThreadGroup[];

void InitSubThread(void)
{
    isysInitGroup(subThreadGroup);
}
