extern char **GetAnimationClass(void *);
extern float GetCurrentGameAnimeTimeScaleRatio(void);
extern void ChangeGameAnimeTimeScaleRatio(float, float);

void nico_timeSlow(void *a)
{
    char **anim = GetAnimationClass(a);
    float rate = 0.75f;
    float cur = GetCurrentGameAnimeTimeScaleRatio();

    ChangeGameAnimeTimeScaleRatio(rate, (rate - cur) * 30.0f / (float)*(unsigned char *)(*anim + 0x44));
}
