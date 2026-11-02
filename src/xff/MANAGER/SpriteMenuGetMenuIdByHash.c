typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char *parts; unsigned int flags; char pad[0x38]; } Layer;
typedef struct { int a; int hash; char pad[0xC]; int id; } PartDef;
typedef struct { PartDef *def; char pad[0x18]; } Part;

int SpriteMenuGetMenuIdByHash(unsigned char *o, int layerHash, int partHash)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    int id = -1;
    Layer *r = 0;
    int i;

    for (i = 0; i < *(int *)(c + 8); i++) {
        r = &(*(Layer **)(c + 4))[i];
        if (r->def->hash == layerHash)
            break;
    }
    i = 0;
    if ((r->flags >> 4) & 0x3FF) {
        Part *parts = (Part *)r->parts;
        Part *p = parts;
        PartDef *def = p->def;
        goto test;
    loop:
        i++;
        if (i >= (int)((r->flags >> 4) & 0x3FF))
            goto out;
        p = &parts[i];
        def = p->def;
    test:
        if (def->hash != partHash)
            goto loop;
        id = def->id;
    }
out:
    return id;
}
