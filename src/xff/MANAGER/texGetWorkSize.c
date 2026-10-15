int texGetWorkSize(char *t)
{
    int off;
    if (t == 0)
        return 0;
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
    case 0x15 ... 0x1A:
    case 0x1C ... 0x23:
    case 0x25 ... 0x2B:
        off = 0;
        break;
    default:
        off = 0;
        break;
    }
    return off * 3 + 0x118;
}
