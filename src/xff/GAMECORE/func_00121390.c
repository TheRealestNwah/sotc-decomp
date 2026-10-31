typedef struct {
    char pad0[0x18];
    int bgm;
    int stopped;
} BgmWork;

extern void bgmStop(int, int, float);

static void func_00121390(int a0, int a1, int a2, int a3, BgmWork *work)
{
    if (work->bgm != 0) {
        bgmStop(work->bgm, 0, 100.0f);
        work->stopped = 1;
        work->bgm = 0;
    }
}
