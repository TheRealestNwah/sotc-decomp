/* ~107 diffs, 1 word longer (146 vs 145). Adds every live sub-geometry (node+0x44 >= 0) of a character class whose dld resource matches target. First counts the non -2 nodes (do-while with a down counter and movn in the Original) and uses 1/count as the weight when cls+0x418 is set, then calls func_00048F90 with 13 pointer args plus (scale, weight, node+0x54) floats and stack words (resolved +0x28 element, node+0x60, node+0x70, cls+0x304[i], target+0xC & 1). The Original keeps cls in $s1 and the node array in $s0, and loads the stack words (t7, t6, f14, t0, t1, t4, t5) before resolving the +0x28 handle; ours resolves it first and keeps cls in $s2. */
extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}
extern int func_00048F90(void *, void *, void *, void *, void *, void *, void *, void *, float, float, float, void *, void *, void *, void *, void *);

#ifdef NONMATCHING
void AddCharacterClassSubGeometries(void *a0, void *a1, void *a2, char *cls, void *t0, char *target, float scale)
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
        func_00048F90(a0, a1, a2, ref, *(void **)(cls + 0x358), cls + 0x90, t0, geom,
                      scale, inv, *(float *)(e + 0x54),
                      geom != 0 ? dldElement((int *)(geom + 0x28)) : 0,
                      e + 0x60, e + 0x70, (void *)(*(int **)(cls + 0x304))[i],
                      (void *)(*(int *)(target + 0xC) & 1));
    }
}
#endif
