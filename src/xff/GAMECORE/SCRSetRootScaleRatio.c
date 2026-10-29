extern void *GetCharacterClass(void *);
int SCRSetRootScaleRatio(void *actor, float ratio)
{
    char *character = GetCharacterClass(actor);
    if (character != 0) {
        *(float *)(character + 0x570) = ratio;
        return 1;
    }
    return 0;
}
