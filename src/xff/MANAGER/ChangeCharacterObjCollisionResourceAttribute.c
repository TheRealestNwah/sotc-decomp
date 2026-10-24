extern void ChangeLayoutObjCollisionResourceAttribute(unsigned char *, int, int, int, int, int, int);

static inline char *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (char *)object + 0x90;
    case 0x16: return (char *)object + 0x90;
    default: return 0;
    }
}

void ChangeCharacterObjCollisionResourceAttribute(unsigned char *object, int a, int b, int c, int d, int e, int f)
{
    unsigned char **parts = (unsigned char **)(characterClass(object) + 0x5B0);
    int i;
    for (i = 3; i != -1; --i) {
        unsigned char *part = *parts++;
        if (part != 0)
            ChangeLayoutObjCollisionResourceAttribute(part, a, b, c, d, e, f);
    }
    ChangeLayoutObjCollisionResourceAttribute(object, a, b, c, d, e, f);
}
