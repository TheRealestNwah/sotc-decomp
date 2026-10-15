extern char gcGlobalVar[];
typedef struct { char pad[0x1AC]; volatile int busy; } GVar;
extern void *isysGetThisSubThread(void);
extern void isysLetterObjDiscardLetterAll(void *);
extern void isysSleepSubThread(void);
extern void scrRun(void);

void st_playObjAnim(void)
{
    void *t = isysGetThisSubThread();
    isysLetterObjDiscardLetterAll(t);
    isysSleepSubThread();
    while (((GVar *)gcGlobalVar)->busy != 0) {
        isysLetterObjDiscardLetterAll(t);
        isysSleepSubThread();
    }
    for (;;)
        scrRun();
}
