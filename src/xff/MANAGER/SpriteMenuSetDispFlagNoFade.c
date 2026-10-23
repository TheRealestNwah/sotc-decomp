static void func_00098948(void *);

void SpriteMenuSetDispFlagNoFade(unsigned char *o, int i, int disp)
{
    int off = i * 0x44;
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    char *e = *(char **)(c + 4) + off;

    if (disp) {
        switch (*(int *)(e + 8) & 0xF) {
        case 0:
        case 4:
        case 5:
            *(int *)(e + 8) = (*(int *)(e + 8) & ~0xF) | 3;
            func_00098948(e);
            return;
        }
    } else {
        switch (*(int *)(e + 8) & 0xF) {
        case 1:
        case 2:
        case 3:
            *(int *)(e + 8) = *(int *)(e + 8) & ~0xF;
            func_00098948(e);
            break;
        }
    }
}
