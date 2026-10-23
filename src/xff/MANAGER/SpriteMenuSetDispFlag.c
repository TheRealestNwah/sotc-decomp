void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp)
{
    int off = i * 0x44;
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    char *e = *(char **)(c + 4) + off;

    if (disp) {
        switch (*(int *)(e + 8) & 0xF) {
        case 0:
        case 4:
        case 5:
            *(int *)(e + 8) = (*(int *)(e + 8) & ~0xF) | 1;
            break;
        }
    } else {
        switch (*(int *)(e + 8) & 0xF) {
        case 1:
        case 2:
        case 3:
            *(int *)(e + 8) = (*(int *)(e + 8) & ~0xF) | 4;
            break;
        }
    }
}
