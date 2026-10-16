typedef struct {
    int ref;
    char pad[0xBC];
} CamLws;

extern CamLws B_0015DC70[];

int stop_camera_lws_animation_callback(unsigned int i)
{
    if (i < 10) {
        B_0015DC70[i].ref = 0;
        return 1;
    }
    return 0;
}
