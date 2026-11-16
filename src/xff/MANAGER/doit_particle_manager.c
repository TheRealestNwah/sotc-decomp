/* Parked: 7 diffs. Steps three frame timers (an inline helper per timer), calls func_000BF318, runs doit_particle_geodisp and the auto-free check over the particle group, then for passes 4..0 updates every emitter whose definition pass matches through func_000C5650. Remaining: the store of the third timer's dt (swc1 $f13) is scheduled earlier than in the Original. Reordering stores, calls and the global writes did not help, and a 25-minute permuter run found nothing better. */
#ifdef NONMATCHING
typedef struct {
    float dt;
    float half;
    float accum;
    int ticks;
} ParticleTimer;

typedef struct Emitter {
    int *def;
    char x4[0xC];
    char body[0x198];
    int x1A8;
    int pad;
    struct Emitter *next;
} Emitter;

extern void auto_end_check_and_check_free_particle_geodisp(int *);
extern void doit_particle_geodisp(int);
extern void func_000BF318(int);
extern int func_000C5650(void *, int);
extern Emitter **get_top_emitter_list_from_particle_geodisp(int);
extern void isysGroupForExit(int, int);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);

extern char B_001499C0[];
extern ParticleTimer B_001499C8;
extern ParticleTimer B_001499D8;
extern ParticleTimer B_001499E8;
extern int D_001370D0;
extern int D_001370D4;
extern int D_001370DC;
extern int D_001370E4;

static inline void stepTimer(ParticleTimer *t, float dt)
{
    t->dt = dt;
    t->half = dt * 0.5f * dt;
    t->accum += dt;
    t->ticks = (int)(t->accum * 30.0f);
    t->accum -= (float)t->ticks * 0.033333328f;
}

void doit_particle_manager(int a0, int a1, int a2, int a3, float dt0, float dt1)
{
    int *it;
    int member = 0;
    int pass;
    int *it2;
    int m2;

    D_001370D0 = a0;
    D_001370D4 = a1;
    D_001370DC = a2;
    stepTimer(&B_001499C8, dt0);
    stepTimer(&B_001499D8, 0.033333335f);
    stepTimer(&B_001499E8, dt1);
    func_000BF318(a3);
    for (it = isysGroupForFirst(B_001499C0, 0); it != 0; it = isysGroupForNext(it, 0)) {
        int g;
        member = *it;
        g = member;
        doit_particle_geodisp(member);
        auto_end_check_and_check_free_particle_geodisp(&g);
    }
    if (member != 0)
        isysGroupForExit(member, 0);
    D_001370E4 = 0;
    for (pass = 4; pass >= 0; pass--) {
        m2 = 0;
        for (it2 = isysGroupForFirst(B_001499C0, 0); it2 != 0; it2 = isysGroupForNext(it2, 0)) {
            Emitter *e;
            m2 = *it2;
            for (e = *get_top_emitter_list_from_particle_geodisp(m2); e != 0; e = e->next) {
                int *d = e->def;
                if (d[10] == pass)
                    {
                    char *b = e->body;
                    *(int *)(b + 0x198) = func_000C5650(b, d[18]);
                }
            }
        }
        if (m2 != 0)
            isysGroupForExit(m2, 0);
    }
}
#endif
