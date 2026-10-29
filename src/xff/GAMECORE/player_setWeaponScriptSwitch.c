extern int *DldSysUndefSymbol;
static inline int resourceCount(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? t[3] : 0;
}
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}
typedef struct { char pad0[0x14]; unsigned int first, second; } WeaponScriptDefinition;
typedef struct { char pad0[0x111C]; void *first, *second; } CharacterClass;
extern CharacterClass *GetCharacterClass(void *);
void player_setWeaponScriptSwitch(void *actor, WeaponScriptDefinition *weapon)
{
    CharacterClass *character = GetCharacterClass(actor);
    character->first = dldResolve(&weapon->first);
    character = GetCharacterClass(actor);
    character->second = dldResolve(&weapon->second);
}
