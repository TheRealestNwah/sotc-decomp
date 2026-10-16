typedef struct {
    char *obj;
    char pad4[0x18];
} AnimalEnt;

typedef struct {
    int num;
    char pad4[0x14];
    AnimalEnt ent[1];
} AnimalTable;

extern AnimalTable B_0019B870;
extern int perceptionExec(void *, void *, float *, void *);

char *getNearInterestSmallAnimal(void *a, void *b)
{
    float buf[4];
    AnimalTable *t = &B_0019B870;
    int i;
    char *o;

    for (i = 0; i < t->num; i++) {
        o = t->ent[i].obj;
        if (o != 0 && perceptionExec(a, b, buf, o + 0x20))
            return o;
    }
    return 0;
}
