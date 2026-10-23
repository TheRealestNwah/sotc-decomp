typedef struct {
    int flags;
    int id;
    int pad8[2];
    int data;
    int pad14[2];
} Vab;

extern Vab B_000C3718[20];

Vab *sndVabCreate(void)
{
    Vab *v;
    int i;

    for (i = 0; i < 20; i++) {
        if (!(B_000C3718[i].flags & 1)) {
            goto found;
        }
    }
    return 0;
found:
    v = &B_000C3718[i];
    v->flags |= 1;
    B_000C3718[i].id = -1;
    B_000C3718[i].data = 0;
    return v;
}
