extern int DldSysUndefSymbol;
extern char *GetCharacterClass(void *);
extern void *GetGeometryPointerObject(void *);
extern void CharaCtrlSetOutsideScriptCtrlStatus(void *, int);

void SCRSetScriptKeyToWallObject(void *a, unsigned int *h)
{
    char *cls = GetCharacterClass(a);

    if (*(int *)(cls + 0xF3C) != 0) {
        void *o = GetGeometryPointerObject(cls + 0xEF0);

        if (o != 0) {
            unsigned int v = *h;
            int off = v & 0x3FFFF;
            char *t = off != 0 ? *(char **)((char *)h - off) : 0;
            char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;

            CharaCtrlSetOutsideScriptCtrlStatus(o, *(int *)(p + 4));
        }
    }
}
