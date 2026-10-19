extern void *DldSysUndefSymbol;
typedef struct { int unknown; signed int priority : 28; unsigned int flags : 4; char rest[88]; } FsEffect;
extern void *D_001303E0;
static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}
void fsEffectSetParamSheetSeg(unsigned int *reference)
{
    FsEffect *effect = (FsEffect *)resourceData(reference);
    if (effect && (!D_001303E0 ||
        effect->priority >= ((FsEffect *)D_001303E0)->priority))
        D_001303E0 = effect;
}


