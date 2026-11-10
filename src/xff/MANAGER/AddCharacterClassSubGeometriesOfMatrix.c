/* ~120 diffs, 5 words short (120 vs 125). Matrix variant of AddCharacterClassSubGeometries: same node count / weight loop (do-while with movn in the Original), then func_0004A5F8(a0, a1, fp, cls+0x90, t0, t1, node+4, node+0x60, weight, node+0x54, scale, stack: node+0x70, cls+0x304[i], target+0xC & 1) for each live node whose dld resource equals target. The Original keeps cls in $s1 / node array in $s0 and builds the stack words after the dld test; ours reorders those loads and the counting loop. */
extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}
extern int func_0004A5F8(void *, void *, void *, void *, void *, void *, void *, void *, float, float, float, void *, void *, int);

#ifdef NONMATCHING
void AddCharacterClassSubGeometriesOfMatrix(void *a0, void *a1, char *cls, void *fp, void *t0, void *t1, char *target, float scale)
{
    int n = *(int *)(cls + 0x3FC);
    char *arr = *(char **)(cls + 0x30C);
    int count = 0;
    int i;
    char *e;
    float inv;

    for (i = 0, e = arr; i < n; i++, e += 0x80)
        if (*(int *)(e + 0x44) != -2)
            count++;
    if (count == 0)
        return;
    inv = 1.0f;
    if (*(int *)(cls + 0x418) != 0)
        inv = 1.0f / (float)count;
    for (i = 0, e = arr; i < n; i++, e += 0x80) {
        char *geom;
        int *ref;

        if (*(int *)(e + 0x44) < 0)
            continue;
        ref = (int *)(e + 4);
        geom = *(char **)ref;
        if (dldElement((int *)(geom + 8)) != target)
            continue;
        func_0004A5F8(a0, a1, fp, cls + 0x90, t0, t1, ref, e + 0x60,
                      inv, *(float *)(e + 0x54), scale,
                      e + 0x70, (void *)(*(int **)(cls + 0x304))[i],
                      *(int *)(target + 0xC) & 1);
    }
}
#endif
