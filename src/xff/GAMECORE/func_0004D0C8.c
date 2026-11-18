typedef struct {
    int emitter;
    char *owner;
    int state;
    void *self;
} EffectSlot;

typedef struct {
    int kind;
    char pad4[0x1C - 0x4];
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
extern char ZeroPoint[];
extern char IdentityQuaternion[];
extern void SetGeometryPointerGlobalState(void *, void *, void *);
extern int get_particle_effect_id_from_sheet(int sheet);
extern int stop_particle_emitter_geometry_pointer_reference(int id, int emitter);
extern int end_particle_emitter(int id, int emitter, int flag);

static void func_0004D0C8(WeakPointEffect *e, int flag)
{
    int sheets[2][4] = {
        { SParticleSheetData_S_WEAKNESS_BASE, SParticleSheetData_S_WEAKNESS_PARTICLE, SParticleSheetData_S_WEAKNESS_FLARE,
          SParticleSheetData_S_WEAKNESS },
        { SParticleSheetData_S_TRIGGER_BASE, SParticleSheetData_S_TRIGGER_PARTICLE, SParticleSheetData_S_TRIGGER_FLARE,
          SParticleSheetData_S_TRIGGER },
    };
    EffectSlot *s = e->slot;
    int i;

    for (i = 0; i < 4; i++, s++) {
        if (s->emitter != 0) {
            if (flag) {
                SetGeometryPointerGlobalState(s->owner + 0xD0, ZeroPoint, IdentityQuaternion);
                stop_particle_emitter_geometry_pointer_reference(get_particle_effect_id_from_sheet(sheets[e->kind][i]), s->emitter);
            }
            end_particle_emitter(get_particle_effect_id_from_sheet(sheets[e->kind][i]), s->emitter, 0);
            s->state = 3;
            s->self = e;
        }
    }
}
