extern void *GetCharacterClass(void *);
extern char *GetScrLwsOriClass(unsigned char *);
static int func_00056C50(unsigned char *, float);
static int func_00056F60(unsigned char *, float);
static void ResetCharacterClassAnimeFrameTableInfo(char *);
int GetMainAnimation(unsigned char *obj, float delta)
{
    char *cls;
    if (delta == 0.0f)
        return 0;
    cls = GetCharacterClass(obj);
    if (*(int *)(cls + 0x1E4) == 0) {
        int result = 0;
        switch (*(int *)(cls + 0x1070)) {
        case 0: result = func_00056C50(obj, delta); break;
        case 1: result = func_00056F60(obj, delta); break;
        }
        if (!result)
            return 0;
        if (*(signed char *)(cls + 0x360))
            ResetCharacterClassAnimeFrameTableInfo(cls);
    }
    if (GetScrLwsOriClass(obj))
        GetCharacterClass(obj);
    return 1;
}