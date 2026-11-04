typedef struct {
    char pad0[0x24];
    int id;
    char pad28[0x50 - 0x28];
    char pos[0x40];
    float f90;
    float f94;
    float f98;
    float pad9C;
    float fA0;
    char padA4[0x274 - 0xA4];
    int state;
    char pad278[0x324 - 0x278];
    float f324;
    char pad328[0x340 - 0x328];
    float f340;
    float f344;
    float f348;
} Animal;

typedef struct {
    char pad0[0xC];
    float fC;
    float f10;
    char pad14[0x30 - 0x14];
    char pos[0x10];
} Target;

extern int AI_CheckInAnimalLayout(void *, void *);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);

#define FABS(x) ((x) < 0.0f ? -(x) : (x))

static int func_000A01D0(Animal *a, Target *t)
{
    float r;
    char *lay;
    char *ch;
    int ok;

    r = a->f98 / a->f90;
    if (a->state != 7) {
        return 0;
    }
    if (3.0f < a->f324) {
        return 0;
    }
    if (a->fA0 < 0.1736481f) {
        return 0;
    }
    if (r < 0.1736481f) {
        return 0;
    }
    if (0.7071066498756409f < r) {
        return 0;
    }
    ok = AI_CheckInAnimalLayout(t->pos, a->pos);
    if (!ok) {
        return 0;
    }
    if (a->f94 < 20.0f) {
        return 0;
    }
    if (t->fC < t->f10 * 0.5f) {
        return 0;
    }
    lay = GetLayoutClass(a->id);
    ch = GetCharacterClass(a->id);
    ok = 0;
    if (*(int *)(lay + 0x124) != 0 && ch[0x362] == 0) {
        if (FABS(a->f344) > FABS(a->f340) && FABS(a->f344) > FABS(a->f348)) {
            ok = 0;
        } else {
            ok = 1;
        }
    }
    return ok != 0;
}
