extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(unsigned char *);
extern void scrRun(void);
extern unsigned char gcGlobalVar[];

static inline unsigned char *getGlobals(void)
{
    return gcGlobalVar;
}

void st_defaultAI(void)
{
    int self = (int)isysGetThisSubThread();
    float last = 0.0f;
    GetLayoutClass((unsigned char *)self);
    for (;;) {
        float now = *(float *)(getGlobals() + 0x178);
        if (now - last > 10.0f) {
            last = now;
        }
        scrRun();
    }
}
