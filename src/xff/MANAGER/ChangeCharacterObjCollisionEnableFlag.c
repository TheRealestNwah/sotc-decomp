extern void SetLayoutObjCollisionEnableFlag(unsigned char *, int);

static inline char *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (char *)object + 0x90;
    case 0x16: return (char *)object + 0x90;
    default: return 0;
    }
}

void ChangeCharacterObjCollisionEnableFlag(unsigned char *object, int flag)
{
    unsigned char **parts = (unsigned char **)(characterClass(object) + 0x5B0);
    int i;
    for (i = 3; i != -1; --i) {
        unsigned char *part = *parts++;
        if (part != 0)
            SetLayoutObjCollisionEnableFlag(part, flag);
    }
    SetLayoutObjCollisionEnableFlag(object, flag);
}
