extern void ChangeCharacterObjControlTarget(unsigned char *, unsigned char *);
extern void CopyGeometryPointer(void *, void *);

static inline char *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (char *)object + 0x90;
    case 0x16: return (char *)object + 0x90;
    default: return 0;
    }
}

void DebugResetCharacterObjControlTarget(unsigned char *object, unsigned char *target)
{
    char *chara = characterClass(object);
    char *other = characterClass(target);
    unsigned char *current = *(unsigned char **)(chara + 0x950);

    *(unsigned char **)(characterClass(current) + 0x960) = current;
    ChangeCharacterObjControlTarget(object, target);
    *(unsigned char **)(other + 0x960) = object;
    if (object != target) {
        other[0x9C5] = 1;
        CopyGeometryPointer(other + 0x970, chara + 0xC0);
    }
}
