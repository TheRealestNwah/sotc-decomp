typedef int s128 __attribute__((mode(TI)));

typedef struct Particle Particle;
struct Particle {
    s128 pos;
    float sc[2];
    char pad18[8];
    int active;
    float pad24;
    float life;
    float size;
    char pad30[4];
    void *owner;
    Particle *next;
};

typedef struct {
    char pad0[0x34];
    float range;
    char pad38[8];
    float count;
    float emitLimit;
    char pad48[0x14];
    float size;
    char pad60[4];
    float decay;
    float decayMin;
    float spread;
} EmitParams;

typedef struct {
    char pad0[0xFC];
    float rA;
    float rB;
    char pad104[0x10];
    EmitParams *params;
    char pad118[8];
    int slotsPad;
    Particle *freeList;
} Emitter;

typedef struct {
    Emitter *em;
    float rate;
    float amount;
    float limit;
    float pad10;
    int counter;
    char pad18[8];
    s128 origin;
} Spawner;

extern float AI_GetInterRatio(void *, float, float, float, float, float);
extern float iosGetRandom(void);
extern void iosGetSinCosf(void *, float);
extern char *iosgluGetCameraContext(void *);

#ifdef NONMATCHING /* 131 diffs, same word count: particle spawner; register assignment and float constant hoisting */
void func_00052558(Spawner *sp)
{
    float off[4] __attribute__((aligned(16)));
    s128 cam;
    int n = 0;
    float fn = (float)n;
    Emitter *em = sp->em;
    Particle **slot = (Particle **)((char *)em + 0x124);

    if (fn < em->params->count) {
        do {
            Particle *p = *slot;
            float r;

            if (p == 0)
                break;
            cam = *(s128 *)(iosgluGetCameraContext(sp->em) + 0x140);
            em = sp->em;
            r = em->params->range;
            {
                float d;
                __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                     "lqc2 vf6, 0x0(%2)\n"
                                     "vsub.xyzw vf7, vf5, vf6\n"
                                     "vmul.xyz vf7, vf7, vf7\n"
                                     "vaddy.x vf7, vf7, vf7y\n"
                                     "vaddz.x vf7, vf7, vf7z\n"
                                     "qmfc2.ni $2, vf7\n"
                                     "mtc1 $2, %0\n"
                                     : "=f"(d) : "r"(&cam), "r"(&sp->origin) : "$2");
                if (d < r * r) {
                    float v = AI_GetInterRatio(em, sp->rate, fn, 1.0f, em->rA, em->rB) + fn;
                    *slot = p->next;
                    p->active = 1;
                    p->next = 0;
                    p->owner = sp;
                    p->life = v;
                    p->size = sp->em->params->size;
                    if (n == 0) {
                        p->pos = sp->origin;
                    } else {
                        off[0] = (2.0f * iosGetRandom() - 1.0f) * sp->em->params->spread;
                        off[1] = fn;
                        off[2] = (2.0f * iosGetRandom() - 1.0f) * sp->em->params->spread;
                        off[3] = fn;
                        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                             "lqc2 vf6, 0x0(%2)\n"
                                             "vadd.xyz vf5, vf5, vf6\n"
                                             "sqc2 vf5, 0x0(%0)\n"
                                             : : "r"(p), "r"(&sp->origin), "r"(off) : "memory");
                    }
                    iosGetSinCosf((char *)p + 0x10, iosGetRandom() * 6.283185f);
                }
            }
            n++;
            fn = (float)n;
        } while (fn < sp->em->params->count);
    }
    if (n > 0) {
        EmitParams *pr;

        sp->counter++;
        pr = sp->em->params;
        if (pr->emitLimit <= (float)sp->counter || sp->amount < pr->decayMin) {
            sp->rate = 0.0f;
            sp->counter = 0;
        } else {
            sp->rate = sp->rate * pr->decay;
        }
    }
}
#endif
