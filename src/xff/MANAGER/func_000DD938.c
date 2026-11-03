extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
typedef struct { char pad0[0x1C]; int bank; } SepDef;
typedef struct { int pad0; unsigned int handle; unsigned int a : 5; unsigned int b : 7; float volume; } SepSource;
typedef struct { char pad0[0x10]; int bank; union { struct { short a; short b; } s; int i; float f; } p; float vol0; float vol1; char pad20[0x24]; SepSource *source; } SepWork;
extern void sndSepSetDefaultParam(SepWork *);
static inline void *dldElement(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + ((*h >> 18) & 0xFFF) * t->type->size : 0;
}
static int func_000DD938(SepWork *work)
{
    SepSource *source = work->source;
    SepDef *def = dldElement(&source->handle);
    if (def == 0)
        return -1;
    if ((work->bank = def->bank) == 0)
        return -1;
    work->p.s.a = source->a;
    work->p.s.b = source->b;
    work->vol1 = work->vol0 = source->volume;
    sndSepSetDefaultParam(work);
    return 0;
}
