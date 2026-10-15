typedef struct { char pad[0x38]; int lo : 21; int v : 10; int hi : 1; char pad2[8]; } MenuItem;

int SpriteMenuGetSelectSubMenuId(unsigned char *p)
{
    unsigned char *m = p[8] == 0x21 ? p + 0x90 : 0;
    int i = *(int *)(m + 0xC);
    if (i != -1) {
        MenuItem *e = *(MenuItem **)(m + 4) + i;
        return e->v;
    }
    return -1;
}
