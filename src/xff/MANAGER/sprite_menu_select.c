typedef struct {
    int unk0;
    int hash;
    int unk8;
    int value;
    unsigned int flags;
    int menuId;
} PartsDef;

typedef struct {
    PartsDef *def;
    int unk4;
    int unk8;
    int value;
    int unk10;
    int unk14;
    int unk18;
} Parts;

typedef struct {
    PartsDef *def;
    Parts *parts;
    unsigned int flag : 4;
    unsigned int nparts : 10;
    unsigned int unk8 : 18;
    char pad[0x2C];
    unsigned int unk38; /* selectMenuId in bits 11..20, subMenuId in bits 21..30 */
    int unk3C;
    int unk40;
} Layer;

typedef struct {
    int unk0;
    Layer *layers;
    int nlayers;
    int selectLayer;
} Menu;

static inline Menu *getMenu(unsigned char *o)
{
    if (o[8] == 0x21)
        return (Menu *)(o + 0x90);
    return 0;
}

static inline Parts *getSelectParts(Layer *l)
{
    int i;

    for (i = 0; i < l->nparts; i++) {
        if ((l->parts[i].def->flags & 2) && l->parts[i].def->menuId == ((int)(l->unk38 << 11) >> 22))
            return &l->parts[i];
    }
    return 0;
}

void SpriteMenuSetSliderValue(unsigned char *o, int value)
{
    Menu *c = getMenu(o);
    Layer *l;
    Parts *p;

    if (c->selectLayer == -1)
        return;
    l = &c->layers[c->selectLayer];
    p = getSelectParts(l);
    if (p == 0)
        return;
    if (p->def->flags & 0x100)
        p->value = value;
    else
        l->unk38 = (l->unk38 & 0x801FFFFF) | ((value & 0x3FF) << 21);
}

void SpriteMenuSetSelectSubMenuId(unsigned char *o, int id)
{
    Menu *c = getMenu(o);
    Layer *l;
    Parts *p;

    if (c->selectLayer == -1)
        return;
    l = &c->layers[c->selectLayer];
    p = getSelectParts(l);
    if (p == 0)
        return;
    if (p->def->flags & 0x100)
        p->value = id;
    else
        l->unk38 = (l->unk38 & 0x801FFFFF) | ((id & 0x3FF) << 21);
}
