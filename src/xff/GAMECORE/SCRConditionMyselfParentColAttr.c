extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);

int SCRConditionMyselfParentColAttr(void *actor, int a1, int a2, int a3, long mask, int attr)
{
    char *cls;

    if (*(int *)(GetLayoutClass(actor) + 0x124) == 0) {
        return 0;
    }
    cls = GetCharacterClass(actor);
    if (attr != -1)
        return attr == (*(long *)(cls + 0x690) & mask);
    return (*(long *)(cls + 0x690) & mask) != 0;
}
