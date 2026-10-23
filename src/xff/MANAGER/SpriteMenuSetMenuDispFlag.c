typedef struct {
    char pad[0x10];
    int flags;
    int id;
} SpriteMenuItem;

typedef struct {
    SpriteMenuItem *item;
    char pad[0x18];
} SpriteMenuEntry;

typedef union {
    struct {
        int pad0;
        SpriteMenuEntry *entries;
        unsigned int status : 4;
        unsigned int num : 10;
        unsigned int rest : 18;
        char padC[0x38];
    } s;
    char alias;
} SpriteMenuLayer;

void SpriteMenuSetMenuDispFlag(unsigned char *o, int layer, int id, int disp)
{
    int off = layer * 0x44;
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    SpriteMenuLayer *e = (SpriteMenuLayer *)(*(char **)(c + 4) + off);
    int i;

    for (i = 0; i < e->s.num; i++) {
        SpriteMenuItem *item = e->s.entries[i].item;

        if ((item->flags & 2) && item->id == id) {
            if (disp) {
                item->flags &= ~0x800;
            } else {
                item->flags |= 0x800;
            }
        }
    }
}
