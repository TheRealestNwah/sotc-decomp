extern void *GetCharacterClass(unsigned char *);
extern void *GetScriptAnimationClass(unsigned char *);

void FlushJudgeVolumeObj(unsigned char *p)
{
    switch (p[8]) {
    case 9:
    case 0x16:
        GetCharacterClass(p);
        p = 0;
        break;
    case 0xD:
        GetScriptAnimationClass(p);
        p = 0;
        break;
    }
}
