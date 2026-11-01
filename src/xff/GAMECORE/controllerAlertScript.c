typedef void (*DrawFn)(void *, int, int, int, float);
typedef void (*ExecFn)(void *);

extern char gcGlobalVar[];
extern int D_0017A9A8;
extern float D_0017A9AC;
extern void *isysGetThisSubThread(void);
extern char *GetSpriteMenuClass(void *);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetDispFlagAll(void *, int);
extern int iosPadChkConnect(int);
extern void ischedStop(void);
extern void ischedRestart(void);
extern void scrRun(void);

void controllerAlertScript(void)
{
    int state = 0;
    int cnt = 0;
    void *th = isysGetThisSubThread();
    char *m = GetSpriteMenuClass(th);
    char *g;

    SpriteMenuSetLayer(th, 0);
    g = gcGlobalVar;
    for (;;) {
        switch (state) {
        case 0:
            if (iosPadChkConnect(0) == 0 && D_0017A9A8 == 0) {
                cnt++;
                if (cnt >= 5) {
                    D_0017A9AC = *(float *)(g + 0x168);
                    SpriteMenuSetDispFlagAll(th, 1);
                    state = 1;
                }
            } else {
                cnt = 0;
            }
            break;
        case 1:
            if (*(float *)(g + 0x168) - D_0017A9AC > 1.0f) {
                ischedStop();
                while (iosPadChkConnect(0) == 0)
                    ;
                ischedRestart();
                state = 0;
                SpriteMenuSetDispFlagAll(th, 0);
                cnt = 0;
            }
            break;
        }
        (*(DrawFn *)(m + 0x28))(th, 0, 0, 0, *(float *)(g + 0x170));
        (*(ExecFn *)(m + 0x2C))(th);
        scrRun();
    }
}
