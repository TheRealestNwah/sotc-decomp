extern void ChangeGameAnimeTimeScaleRatio(float, float);
extern char *GetAnimationClass(unsigned char *);
extern float GetCurrentGameAnimeTimeScaleRatio();
extern float GetGameAnimeTimeScaleRatio();

void nico_timeResume(unsigned char *actor)
{
    float temp_f20;
    void **temp_s0;

    temp_s0 = (void **)GetAnimationClass(actor);
    temp_f20 = GetGameAnimeTimeScaleRatio();
    ChangeGameAnimeTimeScaleRatio(temp_f20, ((temp_f20 - GetCurrentGameAnimeTimeScaleRatio()) * 30.0f) / (float) (*(unsigned char *)((char *)(*temp_s0) + 0x45)));
}
