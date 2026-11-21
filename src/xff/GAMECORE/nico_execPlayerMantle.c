#ifdef NONMATCHING
/* 10 diffs, same length (125 words); several of the 10 are only relocation addends. Sibling of nico_execPlayerFringe (same getClothDynamics call shape, but with a per-index cloth parameter block built on the stack: index 0 -> {-0.03, -0.05, -0.08, -0.1, shorts -1, 0, -0x1000}, index 1 -> {0, -0.05, 0.14, 0.12, shorts 1, -0x800, 0xC00}). GetCharacterClass takes lay[0x194], not obj. The float constants are pinned to the Original's registers ahead of the loop, which gives both their hoist order (-0.08, -0.1, -0.03, -0.05) and the first block's store order. Remaining: the Original hoists the integer constants as -0x800, 0xC00, 1 (ours: 1, -0x800, 0xC00, so the registers rotate), and the second block stores f0 before s10. Pinning the integers or setting them in locals before the loop also hoists -1 / -0x1000 (44 to 76 diffs); a switch changes the branch layout. */
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
    i = 0;
    if (n > 0) {
        register float k8 __asm__("$f27") = -0.08f;
        register float kC __asm__("$f26") = -0.1f;
        register float k0 __asm__("$f25") = -0.03f;
        register float k4 __asm__("$f22") = -0.05f;
        register float b8 __asm__("$f24") = 0.14f;
        register float bC __asm__("$f23") = 0.12f;
        do {
            if (i == 0) {
                a.f0 = k0;
                a.f4 = k4;
                a.f8 = k8;
                a.fC = kC;
                a.s10 = -1;
                a.s12 = 0;
                a.s14 = -0x1000;
                getClothDynamics(p, lay, x, y, arg, func_0007EF98, &a);
            } else if (i == 1) {
                b.f0 = 0;
                b.f4 = k4;
                b.f8 = b8;
                b.fC = bC;
                b.s10 = i;
                b.s12 = -0x800;
                b.s14 = 0xC00;
                getClothDynamics(p, lay, x, y, arg, func_0007EF98, &b);
            }
            i++;
            p += 0x90;
        } while (i < n);
    }
}
#endif
