extern void *isysGetThisSubThread(void);

extern void scrRun(void);

extern void scrInit(void *thread);

void home_test_anim(void)
{
    scrInit(isysGetThisSubThread());
    for (;;) {
        scrRun();
    }
}
