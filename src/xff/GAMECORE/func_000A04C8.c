extern int AI_CheckHorseParent(void *);
extern int AI_CheckInAnimalLayout(void *, void *);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);

#define ABS(x) ((x) < 0 ? -(x) : (x))

static int func_000A04C8(char *ai, char *target)
{
    int side = AI_CheckHorseParent(*(void **)(ai + 0x24));
    char *layout;
    char *chara;

    if (!side)
        return 1;
    if (*(float *)(target + 0x1C) < 6.0f)
        return 1;
    if (!AI_CheckInAnimalLayout(target + 0x30, ai + 0x50))
        return 1;
    layout = GetLayoutClass(*(void **)(ai + 0x24));
    chara = GetCharacterClass(*(void **)(ai + 0x24));
    side = 0;
    if (*(int *)(layout + 0x124) && !*(signed char *)(chara + 0x362)) {
        if (ABS(*(float *)(ai + 0x344)) > ABS(*(float *)(ai + 0x340))) {
            if (ABS(*(float *)(ai + 0x344)) > ABS(*(float *)(ai + 0x348)))
                side = 0;
            else
                side = 1;
        } else {
            side = 1;
        }
    }
    return !side;
}
