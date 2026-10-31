typedef struct { int sp, base, a, start, end, size; } Env;

static inline int countUnusedStack(Env *e)
{
    int i;

    for (i = 0; i < e->size; i++) {
        if (((unsigned char *)e->start)[i] != 0xFE)
            return i;
    }
    return e->size;
}

float isysGetSubThreadStackUse(unsigned char *o)
{
    Env *e;
    int i;

    switch (o[8]) {
    case 6:
    case 9:
    case 11:
    case 12:
    case 13:
    case 14:
    case 22:
    case 29:
    case 33:
        e = (Env *)(o + 0x20);
        break;
    case 7:
    case 8:
    case 10:
    case 15 ... 21:
    case 23 ... 28:
    case 30 ... 32:
        e = 0;
        break;
    default:
        e = 0;
        break;
    }
    i = countUnusedStack(e);
    return 1.0f - (float)i / (float)e->size;
}
