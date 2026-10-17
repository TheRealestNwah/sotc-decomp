extern void *GetCharacterClass(void *);
extern void *GetScriptLayoutClass(unsigned char *);
void *getDamageEnableTargetLayoutClass(void *object)
{
    char *character = GetCharacterClass(object);
    char *found = 0;
    if (character != 0 && *(signed char *)(character + 0x532) != 0)
        found = character;
    if (found == 0) {
        char *layout = GetScriptLayoutClass(object);
        if (layout != 0 && *(int *)(layout + 0x2D0) != 0)
            found = layout + 0x70;
    }
    return found;
}

