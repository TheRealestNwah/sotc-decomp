typedef struct { char pad[0x38]; unsigned int lo : 11; unsigned int id : 10; unsigned int hi : 11; char pad2[8]; } MenuItem;

void SpriteMenuSetSelectMenuId(unsigned char *p, int id)
{
    unsigned char *m = p[8] == 0x21 ? p + 0x90 : 0;
    int i = *(int *)(m + 0xC);
    if (i != -1) {
        MenuItem *e = *(MenuItem **)(m + 4) + i;
        e->id = id;
    }
}
