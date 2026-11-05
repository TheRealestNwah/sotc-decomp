#define ABS(x) ((x) < 0.0f ? -(x) : (x))

extern int AI_CheckHorseParent(int);
extern int AI_CheckInAnimalLayout(void *, void *);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);

static int func_000A0390(char *w, char *t)
{
    char *layout;
    char *chara;
    int r;
    float y;

    if (!AI_CheckHorseParent(*(int *)(w + 0x24)))
        return 0;
    if (*(float *)(t + 0x1C) <= 7.0f)
        return 0;
    r = AI_CheckInAnimalLayout(t + 0x30, w + 0x50);
    if (!r)
        return 0;
    layout = GetLayoutClass(*(int *)(w + 0x24));
    chara = GetCharacterClass(*(int *)(w + 0x24));
    r = 0;
    if (*(int *)(layout + 0x124) != 0) {
        if (*(signed char *)(chara + 0x362) == 0) {
            y = *(float *)(w + 0x344);
            if (ABS(y) > ABS(*(float *)(w + 0x340)) && ABS(y) > ABS(*(float *)(w + 0x348)))
                r = 0;
            else
                r = 1;
        }
    }
    return r != 0;
}
