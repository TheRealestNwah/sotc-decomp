/* Weak-point / trigger glow fade: eases e->level toward e->target by D_0017ABA4 per frame (scaled by gcGlobalVar+0x180 * 30), feeds 1 - level to the blend ratio of each live particle emitter in the four slots (sheet chosen by e->kind) and marks the slot state 2, then snaps level to target and returns 1 once they are within 0.01. The level store goes through a union so it may alias the slot loads that follow, as in the Original. */
typedef struct {
    int emitter;
    char *owner;
    int state;
    void *self;
} EffectSlot;

typedef struct {
    int kind;
    char pad4[0x10 - 0x4];
    float target;
    float level;
    char pad18[0x1C - 0x18];
    EffectSlot slot[4];
} WeakPointEffect;

extern int SParticleSheetData_S_WEAKNESS_BASE;
extern int SParticleSheetData_S_WEAKNESS_PARTICLE;
extern int SParticleSheetData_S_WEAKNESS_FLARE;
extern int SParticleSheetData_S_WEAKNESS;
extern int SParticleSheetData_S_TRIGGER_BASE;
extern int SParticleSheetData_S_TRIGGER_PARTICLE;
extern int SParticleSheetData_S_TRIGGER_FLARE;
extern int SParticleSheetData_S_TRIGGER;
typedef union {
    float f;
    int i;
} FloatOrInt;

extern char gcGlobalVar[];
extern float D_0017ABA4;
extern void set_npe_blend_ratio_particle_emitter(int sheet, int emitter, float ratio);

static int func_0004D260(WeakPointEffect *e)
{
    int sheets[2][4] = {
        { SParticleSheetData_S_WEAKNESS_BASE, SParticleSheetData_S_WEAKNESS_PARTICLE, SParticleSheetData_S_WEAKNESS_FLARE,
          SParticleSheetData_S_WEAKNESS },
        { SParticleSheetData_S_TRIGGER_BASE, SParticleSheetData_S_TRIGGER_PARTICLE, SParticleSheetData_S_TRIGGER_FLARE,
          SParticleSheetData_S_TRIGGER },
    };
    EffectSlot *s = e->slot;
    int i;
    register int done asm("$20") = 0;
    float d;
    float dt;

    dt = *(float *)(gcGlobalVar + 0x180) * 30.0f;

    ((FloatOrInt *)&e->level)->f = e->level + (e->target - e->level) * D_0017ABA4 * dt;
    for (i = 0; i < 4; i++, s++) {
        if (s->emitter != 0) {
            set_npe_blend_ratio_particle_emitter(sheets[e->kind][i], s->emitter, 1.0f - e->level);
            s->state = 2;
        }
    }
    d = e->level - e->target;
    if (d < 0.0f ? -0.01f < d : d < 0.01f) {
        e->level = e->target;
        done = 1;
    }
    return done;
}
