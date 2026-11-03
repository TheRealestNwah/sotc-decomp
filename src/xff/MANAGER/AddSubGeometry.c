extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
typedef struct { char pad0[0x28]; int handle; } Geometry;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}
extern int func_00048F90(void *, void *, void *, Geometry **, void *, void *, void *, Geometry *, void *, void *, void *, void *, void *);
int AddSubGeometry(void *a, void *b, void *c, Geometry **geometry, void *e, void *f, void *g, void *h, void *i, void *j, void *k)
{
    Geometry *geom = *geometry;
    return func_00048F90(a, b, c, geometry, e, f, g, geom, geom != 0 ? dldElement(&geom->handle) : 0, h, i, j, k);
}
