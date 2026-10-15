typedef struct { char pad[0x38]; int lo : 9; int v : 2; int hi : 21; char pad2[8]; } MenuItem;

int SpriteMenuGetSelectMenuMode(unsigned char *p)
{
    unsigned char *m = p[8] == 0x21 ? p + 0x90 : 0;
    int i = *(int *)(m + 0xC);
    if (i != -1) {
        MenuItem *e = *(MenuItem **)(m + 4) + i;
        return e->v;
    }
    return -1;
}
