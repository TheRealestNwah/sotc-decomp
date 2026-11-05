struct GcGlobal { char pad[0x320]; int key[2]; };
extern struct GcGlobal gcGlobalVar;
extern char padManagerData[];
extern int __gameMode;
extern void func_000BC988(int);

struct FadeEntry {
    float time;
    float alpha;
    float speed;
    int state;
};

extern struct FadeEntry B_0019CCD0[4];

void func_000BCA80(float dt)
{
    struct FadeEntry *e;
    int i;
    int count = 0;
    unsigned int pad = *(unsigned int *)(padManagerData + 8);

    if ((pad & (1 << gcGlobalVar.key[0]) || pad & (1 << gcGlobalVar.key[1])) && !(__gameMode & 1))
        func_000BC988(4);

    e = B_0019CCD0;
    for (i = 3; i >= 0; i--, e++) {
        switch (e->state) {
        case 0:
            e->time += dt;
            if (e->time >= 5.0f)
                count++;
            break;
        case 1:
        case 2:
            e->alpha += e->speed * dt * 30.0f;
            if (e->alpha >= 1.0f) {
                e->alpha = 1.0f;
                goto reset;
            }
            break;
        case 3:
            e->alpha += e->speed * dt * 30.0f;
            if (e->alpha <= 0.0f) {
                e->alpha = 0.0f;
            reset:
                e->state = 0;
                e->speed = 0.0f;
                e->time = 0.0f;
            }
            break;
        }
    }

    if (count == 4) {
        for (i = 0; i < 4; i++) {
            B_0019CCD0[i].state = 3;
            B_0019CCD0[i].speed = -0.049999998f;
        }
    }
}
