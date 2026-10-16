extern char B_0018A970[];
extern float D_0017A9D0;
extern char *GetCharacterClass(void *);
extern int *GetDamageClass(void *);
extern void GetGeometryPointerPosition(float *, void *);
extern void T_0004C940(void *, char *, int, float *, int, int, float, float);

void effect_blood_set(void *obj, void *target, float scale)
{
    char *c = GetCharacterClass(obj);
    float pos[4] __attribute__((aligned(16)));

    if (*GetDamageClass(obj) == 3) {
        int **m;

        GetGeometryPointerPosition(pos, B_0018A970);
        m = *(int ***)(c + 0x144);
        T_0004C940(target, c, *(int *)((char *)m[0] + 0x20), pos, *(int *)((char *)m[3] + 0x104),
                   *(short *)(c + 0x1B4), D_0017A9D0, scale);
    }
}
