typedef struct { int w[2]; unsigned int lo : 14; unsigned int v : 4; unsigned int hi : 14; char pad[56]; } MenuItem;

void SpriteMenuSetLayerPriority(unsigned char *p, int i, int v)
{
    unsigned char *m = p[8] != 0x21 ? 0 : p + 0x90;
    MenuItem *e = *(MenuItem **)(m + 4) + i;
    e->v = v;
}
