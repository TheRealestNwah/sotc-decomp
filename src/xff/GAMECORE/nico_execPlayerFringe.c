extern void *D_0017AEC0;
extern int D_0017AEC4;
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern int getClothDynamics(char *, char *, float, float, int, int (*)(), int);
extern int func_000800B8();
extern int func_00080960();

void nico_execPlayerFringe(void *obj, int arg, float x, float y)
{
    char *lay = GetLayoutClass(obj);
    char *t = *(char **)(lay + 0x178);
    char *p = *(char **)t;
    int n = *(short *)(t + 4);
    char *cc = GetCharacterClass(obj);
    int i;

    if (cc != 0 && *(int *)(cc + 0x1070) != 1)
        D_0017AEC0 = (void *)(D_0017AEC4 = 0);
    if (D_0017AEC0 != 0) {
        for (i = 0; i < n; i++) {
            getClothDynamics(p, lay, x, y, arg, func_000800B8, 0);
            p += 0x90;
        }
    } else {
        for (i = 0; i < n; i++) {
            getClothDynamics(p, lay, x, y, arg, func_00080960, 0);
            p += 0x90;
        }
    }
}
