typedef struct { int anim; char pad[0xBC]; } CamLws;
extern CamLws B_0015DBD0[];

int is_same_camera_lws_animation(unsigned int i, int anim)
{
    if (i < 10 && anim != 0 && B_0015DBD0[i].anim == anim)
        return 1;
    return 0;
}
