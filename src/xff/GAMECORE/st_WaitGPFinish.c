extern volatile long gpfinishctr;
extern void scrRun(void);

void st_WaitGPFinish(int n)
{
    long start = gpfinishctr;

    if (gpfinishctr < start + n) {
        do {
            scrRun();
        } while (gpfinishctr < start + n);
    }
}
