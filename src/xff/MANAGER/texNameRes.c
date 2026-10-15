char *texNameRes(char *t)
{
    int off = 0;
    switch (*(int *)(t + 0x1C) & 0x3F) {
    case 0x13:
    case 0x1B:
        off = 0x400;
        break;
    case 0x14:
    case 0x24:
    case 0x2C:
        off = 0x40;
        break;
    }
    return t + *(int *)(t + 0x18) + off;
}
