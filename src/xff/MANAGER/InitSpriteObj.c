extern void *DldSysUndefSymbol;
extern void *iosMallocAlign(void *, int, int);
extern void func_00099118();
extern void func_00098A88(void *heap, void *obj, void *sprite, int arg);

typedef struct {
    void *heap;
    int unk4;
    unsigned char type;
} SpriteObjHeader;

typedef struct {
    int buf;
    int count;
    int used;
    float unkC;
    float unk10;
    int unk14;
    int unk18;
    int color;
    float unk20;
    float unk24;
    float unk28;
    int unk2C;
    float unk30;
    int unk34;
    int unk38;
    float unk3C;
    float unk40;
    float unk44;
    int unk48;
    int unk4C;
    int unk50;
    int func;
} SpriteWork;

typedef struct {
    int unk0;
    unsigned int *ref;
    int count;
    float unkC;
    float unk10;
    float unk14;
    float unk18;
    float unk1C;
    int unk20;
    float unk24;
    float unk28;
    float unk2C;
    float unk30;
    int unk34;
} SpriteDef;

#ifdef NONMATCHING
/* 44 diffs: original keeps every field copy in source order, as if built without strict aliasing (23 diffs with -fno-strict-aliasing) */
int InitSpriteObj(SpriteObjHeader *obj, SpriteDef *def)
{
    void *heap = obj->heap;
    SpriteWork *s = obj->type != 0xE ? 0 : (SpriteWork *)((char *)obj + 0x90);
    unsigned int *ref;
    unsigned int offset;
    char *module;
    int arg;
    float f;

    s->func = (int)func_00099118;
    s->buf = (int)iosMallocAlign(heap, def->count * 4, 0x10);
    s->used = 0;
    s->count = def->count;
    arg = 0;
    module = 0;
    s->unkC = def->unkC;
    s->color = 0xFFFFFF;
    s->unk10 = def->unk10;
    s->unk14 = 0;
    s->unk18 = 0;
    s->unk20 = def->unk14;
    s->unk24 = def->unk18;
    s->unk2C = def->unk20;
    s->unk34 = 0;
    s->unk30 = def->unk24;
    f = def->unk28;
    s->unk3C = f;
    f += def->unk2C;
    s->unk40 = f;
    f += def->unk30;
    s->unk44 = f;
    s->unk28 = def->unk1C;
    s->unk4C = 1;
    s->unk48 = def->unk34;
    s->unk50 = 0;
    ref = def->ref;
    offset = *ref & 0x3FFFF;
    if (offset)
        module = *(char **)((char *)ref - offset);
    if (module && module != DldSysUndefSymbol)
        arg = *(int *)(module + 0x10);
    func_00098A88(heap, obj, s, arg);
    return 1;
}
#endif
