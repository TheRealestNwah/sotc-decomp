extern volatile long gpfinishctr;
extern void scrRun(void);

void st_WaitGPFinish(int frames)
{
    long target = gpfinishctr + frames;

    for (;;) {
        if (gpfinishctr >= target)
            break;
        scrRun();
    }
}
