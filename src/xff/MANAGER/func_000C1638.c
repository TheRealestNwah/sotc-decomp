/* 17 diffs, same size (99 words). An empty `asm volatile("" ::: "memory")` after the vector stores keeps the D_001370DC reload and the beql epilogue delay slot (39 -> 17 diffs); remaining diffs are float register numbering (f3,f0,f1 in the Original) and the second vector block's lw/lq/lwc1 order. Earlier note (39 diffs): Static (alabel) damage probe: if the target's dld element (character node +0xD8 -> +0x44) resolves, builds a position vector from a0+0x98 plus w=1, runs ClipCollisionDirect against the layout class's +0x134 and, when it returns 0, sends a damage letter with a0's quad and a0+0x4C. Structure matches; the only difference is scheduling: the Original reloads D_001370DC after the vector stores and shares the epilogue through a beql delay slot, ours hoists the load above the stores. Permuter base 1135, no improvement. */
extern int DldSysUndefSymbol;
extern int D_001370D4;
extern int D_001370DC;
extern int info[];
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}
typedef int s128 __attribute__((mode(TI)));
extern char *GetLayoutClass(int);
extern int ClipCollisionDirect(void *, int, void *, int);
extern void SendDamageLetter(int, int, void *, void *);

#ifdef NONMATCHING
void func_000C1638(char *a0, char *a1)
{
    char out[0x50];
    long sp50[2];
    float sp60[4];

    if (D_001370DC != 0) {
        if (*(int *)(a1 + 0xD8) != 0) {
            if (dldElement((int *)(*(char **)(a1 + 0xD8) + 0x44)) != 0) {
                sp60[0] = *(float *)(a0 + 0x98);
                sp60[1] = *(float *)(a0 + 0x9C);
                sp60[2] = *(float *)(a0 + 0xA0);
                sp60[3] = 1.0f;
                __asm__ volatile("" ::: "memory");
                sp50[0] = *(long *)&sp60[0];
                sp50[1] = *(long *)&sp60[2];
                if (ClipCollisionDirect(out, *(int *)(GetLayoutClass(D_001370DC) + 0x134), sp50, D_001370D4) == 0) {
                    *(s128 *)sp60 = *(s128 *)a0;
                    sp60[3] = *(float *)(a0 + 0x4C);
                    SendDamageLetter(0, info[2], dldElement((int *)(*(char **)(a1 + 0xD8) + 0x44)), sp60);
                }
            }
        }
    }
}
#endif
