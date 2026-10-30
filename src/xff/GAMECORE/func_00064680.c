typedef struct {
    char unknown000[0x170];
    float animX;
    float animY;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern int D_0017ABD8;
extern int D_0017ABDC;
extern void *isysGetThisSubThread(void);
extern void isysSleepSubThread(void);
extern void *get_main_cameraman_camera_obj(void);
extern int ExecObjectAnimation(void *, void *, float, float);
extern void fadeOut(int, int, float);

static void func_00064680(void)
{
    void *obj = isysGetThisSubThread();
    void *camera;
    float x;
    float y;

    for (;;) {
        camera = get_main_cameraman_camera_obj();
        x = gcGlobalVar.animX;
        y = gcGlobalVar.animY;
        switch (D_0017ABDC) {
        case 0:
            break;
        case 1:
        case 2:
            if (ExecObjectAnimation(obj, camera, x, y)) {
                D_0017ABDC = 3;
                return;
            }
            break;
        case 3:
        case 4:
            ExecObjectAnimation(obj, camera, x, y);
            break;
        case 5:
        case 6:
            if (ExecObjectAnimation(obj, camera, x, y)) {
                if (D_0017ABD8)
                    fadeOut(0, 0, 2.0f);
                D_0017ABDC = 7;
                return;
            }
            break;
        case 7:
        case 8:
            if (ExecObjectAnimation(obj, camera, x, y)) {
                D_0017ABDC = 9;
                return;
            }
            break;
        case 9:
            break;
        }
        isysSleepSubThread();
    }
}
