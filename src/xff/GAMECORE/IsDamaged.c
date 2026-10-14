typedef struct {
    int state;
    char pad4[0x60];
    float time;
} DamageClass;

extern DamageClass *GetDamageClass(void);
extern int GetDamagerClassDamageSheetType(DamageClass *);

int IsDamaged(void *unused, int type)
{
    DamageClass *d = GetDamageClass();

    if (d->state == 1 && (type < 0 || GetDamagerClassDamageSheetType(d) == type) && d->time > 0.0f) {
        return 1;
    }
    return 0;
}
