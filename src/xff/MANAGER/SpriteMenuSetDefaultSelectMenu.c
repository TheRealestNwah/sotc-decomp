typedef struct { int w[14]; unsigned int lo : 11; unsigned int v : 10; unsigned int hi : 11; char pad[8]; } MenuItem;

void SpriteMenuSetDefaultSelectMenu(unsigned char *p, int i, int v)
{
    unsigned char *m = p[8] != 0x21 ? 0 : p + 0x90;
    MenuItem *e = *(MenuItem **)(m + 4) + i;
    e->v = v;
}
