#ifdef NONMATCHING
/* 14 diffs, same length (125 words); several of the 14 are only relocation addends. Sibling of nico_execPlayerFringe (same getClothDynamics call shape, but with a per-index cloth parameter block built on the stack: index 0 -> {-0.03, -0.05, -0.08, -0.1, shorts -1, 0, -0x1000}, index 1 -> {0, -0.05, 0.14, 0.12, shorts 1, -0x800, 0xC00}). GetCharacterClass takes lay[0x194], not obj. Remaining differences: the Original stores the first block in offset order (0, 4, 8, C) but hoists the float constants in the order -0.08, -0.1, -0.03, -0.05 (ours hoists in source order, so the stores are reordered), and hoists -0x800 / 0xC00 / 1 into s-regs in a different order; the second block stores f0 before s10. Source-order tweaks fix one and break the other; hoisting the constants into named locals made it much worse (90). Permuter (12 workers, 20 min): best 110 from 120. */
typedef struct {
    float f0;
    float f4;
    float f8;
    float fC;
    short s10;
    short s12;
    short s14;
} ClothParam;

extern int D_0017AEA0;
extern int D_0017AEA8;
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern int getClothDynamics(char *, char *, float, float, int, int (*)(), ClothParam *);
extern int func_0007EF98();

void nico_execPlayerMantle(void *obj, int arg, float x, float y)
{
    char *lay = GetLayoutClass(obj);
    char *t = *(char **)(lay + 0x178);
    char *p = *(char **)t;
    int n = *(short *)(t + 4);
    char *cc;
    int i;
    ClothParam a;
    ClothParam b;

    if (*(void **)(lay + 0x194) != 0 && (cc = GetCharacterClass(*(void **)(lay + 0x194))) != 0 && *(int *)(cc + 0x1070) != 1) {
        D_0017AEA8 = 0;
        D_0017AEA0 = 0;
    }
    for (i = 0; i < n; i++, p += 0x90) {
        if (i == 0) {
            a.f8 = -0.08f;
            a.fC = -0.1f;
            a.f0 = -0.03f;
            a.f4 = -0.05f;
            a.s10 = -1;
            a.s12 = 0;
            a.s14 = -0x1000;
            getClothDynamics(p, lay, x, y, arg, func_0007EF98, &a);
        } else if (i == 1) {
            b.f0 = 0;
            b.f4 = -0.05f;
            b.f8 = 0.14f;
            b.fC = 0.12f;
            b.s12 = -0x800;
            b.s14 = 0xC00;
            b.s10 = i;
            getClothDynamics(p, lay, x, y, arg, func_0007EF98, &b);
        }
    }
}
#endif
