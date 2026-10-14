extern char *GetCharacterClass(void *);

char *DEBUG_get_latest_motion_name(void *actor, char *def)
{
    char *c = GetCharacterClass(actor);
    char **m;
    if (c == 0)
        goto no;
    m = *(char ***)(c + 0x578);
    if (m == 0)
        goto no;
    return *m;
no:
    return def;
}
