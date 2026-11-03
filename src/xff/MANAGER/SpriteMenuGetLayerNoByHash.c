#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char pad[0x40]; } Layer;
int SpriteMenuGetLayerNoByHash(unsigned char *o, int hash)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    int i = 0; int r = -1; if (i < *(int *)(c + 8)) { Layer *l = *(Layer **)(c + 4); do { if (l[i].def->hash == hash) { r = i; break; } i++; } while (i < *(int *)(c + 8)); } return r;
}
#endif
