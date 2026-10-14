extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern void scrRunM(int);
extern void iosDebugPrintHashTable(void *);
extern char rootPtn[];

void st_malloc_test(void)
{
    scrInit(isysGetThisSubThread());
    for (;;) {
        scrRunM(0xB4);
        iosDebugPrintHashTable(rootPtn);
    }
}
