typedef struct {
    int *def;
    void *parts;
    int flags;
    char pad[0x38];
} Layer;

typedef struct {
    int unk0;
    int layers;
    int nlayers;
    int selectLayer;
} Menu;

static inline Menu *getMenu(unsigned char *o)
{
    Menu *c = 0;

    if (o[8] == 0x21)
        c = (Menu *)(o + 0x90);
    return c;
}

void SpriteMenuSetLayer(unsigned char *o, int no)
{
    Menu *c = getMenu(o);
    Layer *l = &((Layer *)c->layers)[c->selectLayer];

    if (c->selectLayer != no) {
        l->flags &= ~0x100000;
        c->selectLayer = no;
        l = &((Layer *)c->layers)[no];
        l->flags |= 0x100000;
    }
}
