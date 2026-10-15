extern char *GetCharacterClass(unsigned char *);
extern char *GetScriptAnimationClass(unsigned char *);

char *GetJudgeVolumeClass(unsigned char *p)
{
    char *r;
    switch (p[8]) {
    case 9:
    case 0x16:
        r = GetCharacterClass(p) + 0x2A0;
        break;
    case 0xD:
        r = *(char **)(GetScriptAnimationClass(p) + 0x33C);
        break;
    default:
        r = 0;
        break;
    }
    return r;
}
