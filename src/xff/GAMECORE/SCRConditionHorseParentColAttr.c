extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);

int SCRConditionHorseParentColAttr(void *actor, int a1, int a2, int a3, long mask, int attr)
{
    void *obj = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    char *cls;

    if (obj != 0) {
        if (*(int *)(GetLayoutClass(obj) + 0x124) != 0) {
            cls = GetCharacterClass(obj);
            if (attr != -1)
                return attr == (*(long *)(cls + 0x690) & mask);
            return (*(long *)(cls + 0x690) & mask) != 0;
        }
    }
    return 0;
}
