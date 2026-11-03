#ifdef NONMATCHING
/* Close: same layer-search codegen gap as SpriteMenuSetDispFlagByHash. */
typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char pad[0x40]; } Layer;
int SpriteMenuGetLayerNoByHash(unsigned char *o, int hash)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    int no = -1;
    int i = 0;

    if (*(int *)(c + 8) > 0) {
        Layer *layers = *(Layer **)(c + 4);
        Layer *p = layers;
        LayerDef *def = p->def;
        goto test;
    loop:
        i++;
        if (i >= *(int *)(c + 8))
            goto out;
        p = &layers[i];
        def = p->def;
    test:
        if (def->hash != hash)
            goto loop;
        no = i;
    }
out:
    return no;
}

#endif
