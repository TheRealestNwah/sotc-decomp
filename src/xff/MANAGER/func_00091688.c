typedef struct {
    char pad0[0x40];
    char shape[0x90 - 0x40];
    float damage[2];
    char pad98[0x134 - 0x98];
    int attacker;
    int *pos;
    int part;
} DamageWork;

extern int info[];
extern void SendVolumeShapeDamageLetter(void *, int, int, int, int, int, float *, void *);

static void func_00091688(void *obj, DamageWork *w)
{
    float *d = w->damage;

    if (0.001f < d[1])
        SendVolumeShapeDamageLetter(obj, info[2], w->pos[1], w->pos[0], w->attacker, w->part, d, w->shape);
}
