typedef struct {
    char data[0xC0];
} CameraLwsAnime;

extern CameraLwsAnime B_0015DBD0[10];
extern void func_000E5CF8(CameraLwsAnime *, int, int, float);

void doit_camera_lws_animation_manager(int arg0, int arg1, float time)
{
    int i;

    for (i = 0; i < 10; i++) {
        func_000E5CF8(&B_0015DBD0[i], arg0, arg1, time);
    }
}
