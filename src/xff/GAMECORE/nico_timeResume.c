extern void ChangeGameAnimeTimeScaleRatio(float, float);
extern void **GetAnimationClass();
extern float GetCurrentGameAnimeTimeScaleRatio();
extern float GetGameAnimeTimeScaleRatio();

void nico_timeResume(void)
{
    float temp_f20;
    void **temp_s0;

    temp_s0 = GetAnimationClass();
    temp_f20 = GetGameAnimeTimeScaleRatio();
    ChangeGameAnimeTimeScaleRatio(temp_f20, ((temp_f20 - GetCurrentGameAnimeTimeScaleRatio()) * 30.0f) / (float) (*(unsigned char *)((char *)(*temp_s0) + 0x45)));
}
