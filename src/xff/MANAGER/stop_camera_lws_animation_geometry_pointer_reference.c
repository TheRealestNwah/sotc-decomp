typedef struct {
    int ref;
    char pad[0xBC];
} CamLws;

extern CamLws B_0015DC18[];

int stop_camera_lws_animation_geometry_pointer_reference(unsigned int i)
{
    if (i < 10) {
        B_0015DC18[i].ref = 0;
        return 1;
    }
    return 0;
}
