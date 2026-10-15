typedef int s128 __attribute__((mode(TI)));
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void scrRunM(int);

void fallenRockMain(s128 *p)
{
    char *l = GetLayoutClass(isysGetThisSubThread());
    for (;;) {
        if (((int *)p)[4] != 0)
            **(s128 **)(l + 0x134) = *p;
        scrRunM(1);
    }
}
