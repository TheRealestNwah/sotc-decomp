extern char *GetLayoutClass(void *);

static inline char *charClass(char *o)
{
    char *cls;

    switch (((unsigned char *)o)[8]) {
    case 9:
        cls = o + 0x90;
        break;
    case 0x16:
        cls = o + 0x90;
        break;
    default:
        cls = 0;
    }
    return cls;
}

int GetParentCharColAttr(long *out, char *o)
{
    char *l = GetLayoutClass(o);
    char *c;

    if (l != 0 && *(int *)(l + 0x124) != 0) {
        c = charClass(o);
        if (c != 0) {
            *out = *(long *)(c + 0x690);
            return 1;
        }
    }
    *out = 0;
    return 0;
}
