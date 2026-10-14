typedef struct {
    int state;
    char pad4[0x60];
    float time;
} DamageClass;

extern void *GetDamageClass(void *);
extern int GetDamagerClassDamageSheetType(DamageClass *);

int IsDamaged(void *actor, int type)
{
    DamageClass *d = GetDamageClass(actor);

    if (d->state == 1 && (type < 0 || GetDamagerClassDamageSheetType(d) == type) && d->time > 0.0f) {
        return 1;
    }
    return 0;
}
