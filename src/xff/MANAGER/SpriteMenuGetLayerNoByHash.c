#ifdef NONMATCHING
/* Parked: 16 diffs (was 24). The explicit count>0 test adds a second blez; plain for loops without it give 27. */
typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char pad[0x40]; } Layer;
int SpriteMenuGetLayerNoByHash(unsigned char *o, int hash)
{
    unsigned char *c;
    int no = -1;
    int i;

    c = 0;
    if (o[8] == 0x21)
        c = o + 0x90;

    if (*(int *)(c + 8) > 0) { Layer *layers = *(Layer **)(c + 4); for (i = 0; i < *(int *)(c + 8); i++) { if (layers[i].def->hash == hash) { no = i; break; } } }
    return no;
}

#endif
