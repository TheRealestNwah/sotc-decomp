extern int *DldSysUndefSymbol;
extern int strcmp(const char *, const char *);
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
typedef struct { int flags; const char *name; } EffectDef;
typedef struct { int value; unsigned int handle; } AttributeRelation;
static inline int resourceCount(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? t[3] : 0;
}
static inline void *resourceData(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (void *)t[4] : 0;
}
static inline void *dldElement(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + ((*h >> 18) & 0xFFF) * t->type->size : 0;
}
EffectDef *GetAttributeRelationEffectDefByName(int *out, unsigned int *resource, const char *name)
{
    int count = resourceCount(resource);
    if (count != 0) {
        AttributeRelation *relation = resourceData(resource);
        for (; count != 0; count--, relation++) {
            EffectDef *effect = dldElement(&relation->handle);
            if (strcmp(effect->name, name) == 0) {
                *out = relation->value;
                return effect;
            }
        }
    }
    return 0;
}
