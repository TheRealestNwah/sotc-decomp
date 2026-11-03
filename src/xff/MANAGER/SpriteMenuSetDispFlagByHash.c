#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; int pad; unsigned int state : 4; char pad2[0x38]; } Layer;
typedef struct { int pad; Layer *layers; int count; } LayerList;

static inline int GetLayerNo(unsigned char *o, int hash)
{
    LayerList *c = (LayerList *)(o[8] == 0x21 ? o + 0x90 : 0);
    int i;
    int r = -1;
    for (i = 0; i < c->count; i++) {
        if (c->layers[i].def->hash == hash) {
            r = i;
            break;
        }
    }
    return r;
}

void SpriteMenuSetDispFlagByHash(unsigned char *o, int hash, int disp)
{
    int no = GetLayerNo(o, hash);
    LayerList *c = (LayerList *)(o[8] == 0x21 ? o + 0x90 : 0);
    Layer *l = &c->layers[no];

    if (disp) {
        switch (l->state) {
        case 0:
        case 4:
        case 5:
            l->state = 1;
            break;
        }
    } else {
        switch (l->state) {
        case 1:
        case 2:
        case 3:
            l->state = 4;
            break;
        }
    }
}
#endif
