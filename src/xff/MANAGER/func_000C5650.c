extern int D_001370E0;
extern int D_001370E4;
extern int D_001370E8;

static int func_000C5650(char *e, char *d)
{
    int r = 0;
    char *s = *(char **)(d + 0xD4) + *(int *)(e + 0x118) * 0x1BC;

    if (D_001370E0 != 0) {
        int f = 1;

        switch (*(unsigned int *)(s + 0xC)) {
        case 1:
            if (*(int *)(s + 0x18C) == 0)
                f = 0;
            break;
        case 2:
            f = 0;
            break;
        case 3:
            f = 0;
            break;
        }
        if (f != 1) {
            r = 1;
        } else {
            D_001370E4 += *(int *)(e + 0x124);
            if (D_001370E8 != 1 || D_001370E4 < 0x80)
                r = 1;
        }
    }
    return r;
}
