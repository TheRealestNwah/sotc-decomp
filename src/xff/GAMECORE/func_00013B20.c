extern void bgmStop(int, int *, float);
extern int bgmStopChk(int);
extern void scrRun(void);
extern void *memset(void *, int, unsigned int);

typedef struct {
    int pad0[3];
    int bgm;
    int pad10;
    int time;
    int pad18;
} BgmWork;

static void func_00013B20(BgmWork *w)
{
    int handle;
    float fade = 2.0f;

    if (w->time > 99998)
        fade = 0.8f;
    bgmStop(w->bgm, &handle, fade);
    while (!bgmStopChk(handle))
        scrRun();
    memset(w, 0, sizeof(BgmWork));
}
