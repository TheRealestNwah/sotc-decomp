typedef struct {
    int unk0;
    int unk4;
    int unk8;
    float unkC;
} ScreenInfo;

extern float func_000E95C8(float, int);

float get_dist_from_eye_to_screen(ScreenInfo *screen)
{
    return func_000E95C8(screen->unkC, screen->unk4);
}
