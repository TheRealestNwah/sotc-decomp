typedef struct {
    char pad0[0x44];
    void *parent;
    char pad48[0x90 - 0x48];
    float dist;
    char pad94[0x140 - 0x94];
    float range;
    char pad144[4];
    float speed;
} HorseAIWork;

static int func_000AE2A0(HorseAIWork *);
static int func_000ADF90(HorseAIWork *);
static int func_000AE118(HorseAIWork *);
extern int AI_CheckHorseParent(void *);

static int func_000AE498(HorseAIWork *w)
{
    if (20.0f < w->dist)
        return 0;
    if (w->dist < 3.0f && func_000AE2A0(w))
        return 1;
    if (!func_000ADF90(w))
        return 0;
    if (!func_000AE118(w))
        return 0;
    if (AI_CheckHorseParent(w->parent)) {
        if (w->dist < w->range * 4.0f)
            return 1;
        if (w->dist < 3.0f)
            return 1;
        if (w->dist < 10.0f && 5.0f < w->speed)
            return 1;
    } else {
        if (w->dist < 1.0f)
            return 1;
        if (w->dist < w->range + w->range)
            return 1;
        if (w->dist < 3.0f && 5.0f < w->speed)
            return 1;
    }
    return 0;
}
