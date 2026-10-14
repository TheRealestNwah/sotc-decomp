extern char *GetCharacterClass(void *);
char *DEBUG_get_cntrl_mode_name(void *actor, char *def)
{
    char *c = GetCharacterClass(actor);
    if (c != 0)
        return *(char **)(*(char **)(c + 0x750) + 8);
    return def;
}
