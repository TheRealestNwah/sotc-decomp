extern void func_000E5CF8(void *, int, int, float);
extern unsigned char B_0015DBD0[1];

void doit_camera_lws_animation_manager(int first, int second, float time)
{
    int remaining = 9;
    char *work = (char *)B_0015DBD0;

    do {
        func_000E5CF8(work, first, second, time);
        work += 0xC0;
        remaining--;
    } while (remaining >= 0);
}