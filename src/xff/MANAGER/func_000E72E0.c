extern char *GetCharacterClass(void *);
extern int GetCharacterClassCurAnimationFrameRate(char *cls);

static float func_000E72E0(char *p, void *a, void *b)
{
    float rate = 30.0f;
    void *obj = 0;
    int k = *(int *)(p + 0xC);
    float fk = k;

    if (0.0f < fk) {
        rate = fk;
    } else if (k == -1) {
        obj = a;
    } else if (k == -2) {
        obj = b;
    }
    if (obj != 0) {
        rate = GetCharacterClassCurAnimationFrameRate(GetCharacterClass(obj));
        rate *= *(float *)(GetCharacterClass(obj) + 0x524);
    }
    return rate;
}
