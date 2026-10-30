extern char *get_camera_lws_animation_param(void *);
extern void *GAMEUTIL_get_segment_num_and_data(int, void *);
extern int bgmDemoPackagePreload(void *);
extern void bgmDemoPackagePlay(void *);
extern void scriptIntrSignal(int);
extern int ScrIntrDef_DEMO_CONTINUE;
extern int ScrIntrDef_DEMO_PAUSE;

static void func_000ED440(char *w, int start)
{
    void *pkg;

    if (start == 1)
        *(int *)(w + 0x88) = start;
    if (*(void **)(w + 0x90) == 0)
        *(int *)(w + 0x88) = 0;
    if (*(int *)(w + 0x88) == 1) {
        pkg = GAMEUTIL_get_segment_num_and_data(0, get_camera_lws_animation_param(*(void **)(w + 0x90)) + 0x14);
        if (pkg != 0) {
            if (bgmDemoPackagePreload(pkg) == 1) {
                bgmDemoPackagePlay(pkg);
                *(int *)(w + 0x88) = 0;
                if (start == 0)
                    scriptIntrSignal(ScrIntrDef_DEMO_CONTINUE);
            } else if (start == 1) {
                scriptIntrSignal(ScrIntrDef_DEMO_PAUSE);
            }
        } else {
            *(int *)(w + 0x88) = 0;
        }
    }
}
