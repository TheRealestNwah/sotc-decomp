extern void *GetCharacterClass(void *);
extern float ViewIntervalClip(void *, void *, float);
extern void func_0004F910(int, int, int, int, float);
void CharaCtrlAIControl(void *actor, void *target, float interval, float weight)
{
    if (weight != 0.0f) {
        char *character = GetCharacterClass(actor);
        float clipped = ViewIntervalClip(actor, target, interval);
        if (*(int *)(character + 0x1070) != 1)
            weight = clipped;
        func_0004F910((int)actor, 0, 0, 0, weight);
    }
}
