typedef struct {
    int kind;
    char pad4[0x5C - 0x4];
    int emitter;
    char *owner;
    int state;
    void *self;
    char pad6C[0x78 - 0x6C];
} WeakPointEffect;

extern int D_0017ABB0;
extern WeakPointEffect B_0018A9B0[8];
extern int SParticleSheetData_S_WEAKNESS_CONTACT;
extern int SParticleSheetData_S_TRIGGER_CONTACT;
extern char ZeroPoint[];
extern char IdentityQuaternion[];
extern void func_0004D0C8(WeakPointEffect *e, int flag);
extern void func_0004CD68(void);
extern void SetGeometryPointerGlobalState(void *, void *, void *);
extern int get_particle_effect_id_from_sheet(int sheet);
extern int stop_particle_emitter_geometry_pointer_reference(int id, int emitter);
extern int end_particle_emitter(int id, int emitter, int flag);

static inline void stopEffect(WeakPointEffect *e)
{
    int sheets[2] = { SParticleSheetData_S_WEAKNESS_CONTACT, SParticleSheetData_S_TRIGGER_CONTACT };

    if (e->emitter != 0) {
        SetGeometryPointerGlobalState(e->owner + 0xD0, ZeroPoint, IdentityQuaternion);
        stop_particle_emitter_geometry_pointer_reference(get_particle_effect_id_from_sheet(sheets[e->kind]), e->emitter);
        end_particle_emitter(get_particle_effect_id_from_sheet(sheets[e->kind]), e->emitter, 0);
        e->state = 3;
        e->self = e;
    }
}

void init_weakpoint_effect(void)
{
    WeakPointEffect *e = B_0018A9B0;
    int i;

    for (i = 7; i >= 0; i--, e++) {
        func_0004D0C8(e, 1);
        stopEffect(e);
    }
    func_0004CD68();
    D_0017ABB0 = 1;
}
