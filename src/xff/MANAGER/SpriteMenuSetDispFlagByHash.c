#ifdef NONMATCHING
/* Parked: 15 diffs. The plain for loop gives the original layout; left are movz vs movn for the menu pointer and o+0x90 being shared (t4) between the two inlines. Permuter (40 min) found no real improvement. */
typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char pad[0x40]; } Layer;

static inline int GetLayerNo(unsigned char *o, int hash)
{
    unsigned char *c;
    int no = -1;
    int i;

    c = o[8] != 0x21 ? 0 : o + 0x90;
    {
        Layer *layers = *(Layer **)(c + 4);
        for (i = 0; i < *(int *)(c + 8); i++) {
            if (layers[i].def->hash == hash) {
                no = i;
                break;
            }
        }
    }
    return no;
}

static inline void SetDispFlag(unsigned char *o, int i, int disp)
{
    int off = i * 0x44;
    unsigned char *c = o[8] != 0x21 ? 0 : o + 0x90;
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
