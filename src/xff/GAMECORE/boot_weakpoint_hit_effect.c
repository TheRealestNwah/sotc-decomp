typedef struct {
    int values[2];
} SheetList;

typedef struct {
    int id;
    void *emitter;
    int active;
} WeakEmitter;

typedef struct {
    int a;
    char pad4[0x5C - 0x4];
    WeakEmitter hit;
    char pad68[0x78 - 0x68];
} WeakPointEffect;

typedef struct {
    int kind;
    int slot;
    char pad8[0x8];
    char param[0x10];
} WeakHit;

extern int D_0017ABB0;
extern WeakPointEffect B_0018A9B0[8];
extern int SParticleSheetData_S_WEAKNESS_CONTACT;
extern int SParticleSheetData_S_TRIGGER_CONTACT;
extern int get_particle_effect_id_from_sheet(int sheet);
extern int boot_particle_emitter(int effect, void *param, void (*onEnd)(int *done), void *idOut);
extern void *get_particle_emitter_from_emitter_id(int id);
extern void func_0004EAB0(int *done);

void boot_weakpoint_hit_effect(WeakHit *hit)
{
    SheetList sheets;
    SheetList init;
    void *param = hit->param;
    WeakPointEffect *e;
    WeakEmitter *em;
    int kind;

    if (D_0017ABB0 == 0)
        return;
    kind = hit->kind;
    e = &B_0018A9B0[hit->slot];
    e->a = kind;
    init.values[0] = SParticleSheetData_S_WEAKNESS_CONTACT;
    init.values[1] = SParticleSheetData_S_TRIGGER_CONTACT;
    em = &e->hit;
    sheets = init;
    if (em->id == 0) {
        em->id = boot_particle_emitter(get_particle_effect_id_from_sheet(sheets.values[kind]), param,
                                       func_0004EAB0, e);
        em->emitter = get_particle_emitter_from_emitter_id(em->id);
        em->active = 1;
    }
}
