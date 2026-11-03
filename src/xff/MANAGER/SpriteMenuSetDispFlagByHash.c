#ifdef NONMATCHING
/* Close: the inlined layer search computes the menu pointer with movz instead of movn and the loop is laid out differently. */
typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char pad[0x40]; } Layer;

static inline int GetLayerNo(unsigned char *o, int hash)
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

static inline void SetDispFlag(unsigned char *o, int i, int disp)
{
    int off = i * 0x44;
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    char *e = *(char **)(c + 4) + off;

    if (disp) {
        switch (*(int *)(e + 8) & 0xF) {
        case 0:
        case 4:
        case 5:
            *(int *)(e + 8) = (*(int *)(e + 8) & ~0xF) | 1;
            break;
        }
    } else {
        switch (*(int *)(e + 8) & 0xF) {
        case 1:
        case 2:
        case 3:
            *(int *)(e + 8) = (*(int *)(e + 8) & ~0xF) | 4;
            break;
        }
    }
}

void SpriteMenuSetDispFlagByHash(unsigned char *o, int hash, int disp)
{
    SetDispFlag(o, GetLayerNo(o, hash), disp);
}
#endif
