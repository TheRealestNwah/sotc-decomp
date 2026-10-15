extern char *GetCharacterClass(void *);
extern void *GetGeometryPointerObject(void *);
extern void SendCharaNodeParentSetMsg(void *, void *, int);

void nico_ChangePlayerHorseRidingParentWithVCol(void *o)
{
    char *c = GetCharacterClass(o);
    if (*(int *)(c + 0xF3C) != 0) {
        SendCharaNodeParentSetMsg(o, GetGeometryPointerObject(c + 0xEF0), 0x10000);
        c = 0;
    }
}
