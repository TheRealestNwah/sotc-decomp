typedef struct { char pad[0x38]; unsigned int lo : 9; unsigned int mode : 2; unsigned int hi : 21; char pad2[8]; } MenuItem;

void SpriteMenuSetSelectMenuMode(unsigned char *p, int mode)
{
    unsigned char *m = p[8] == 0x21 ? p + 0x90 : 0;
    int i = *(int *)(m + 0xC);
    if (i != -1) {
        MenuItem *e = *(MenuItem **)(m + 4) + i;
        e->mode = mode;
    }
}
