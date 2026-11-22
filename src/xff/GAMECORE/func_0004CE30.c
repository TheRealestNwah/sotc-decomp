typedef struct {
    int id;
    void *em;
    int flag;
    int pad;
} Emit;

typedef struct {
    int kind;
    char pad4[0x4];
    int tex;
    char padC[0x1C - 0xC];
    Emit emit[4];
    char pad5C[0x6C - 0x5C];
    void *lws;
} WeakFx;

typedef struct {
    int id;
    int *ptr;
} LightEnt;

typedef struct {
    int n;
    char pad4[0x14];
    char *types;
} LightHdr;

extern int SParticleSheetData_S_WEAKNESS_BASE;
extern int SParticleSheetData_S_WEAKNESS_PARTICLE;
extern int SParticleSheetData_S_WEAKNESS_FLARE;
extern int SParticleSheetData_S_WEAKNESS;
extern int SParticleSheetData_S_TRIGGER_BASE;
extern int SParticleSheetData_S_TRIGGER_PARTICLE;
extern int SParticleSheetData_S_TRIGGER_FLARE;
extern int SParticleSheetData_S_TRIGGER;
extern void *ScriptAnimationObjDef_BOSS_WEAKNESS_LIGHT;
extern char ZeroPoint[];
extern char IdentityQuaternion[];
extern void *_SCRSetupLWS(void *, int, void *, void *, void *);
extern void _SCRStartLWS(void *, int, int, int);
typedef struct { char pad[0x328]; LightHdr *hdr; char pad32C[0xC]; LightEnt *ents; } AnimCls;
extern AnimCls *GetScriptAnimationClass(void *);
extern void SetGameLightUserParam(void *, void *);
extern void SetGameLightUserFunc(void *, void *);
extern int chkBossWeakTexExist(int);
extern int chkBossTrigTexExist(int);
extern int get_particle_effect_id_from_sheet(int);
extern int boot_particle_emitter(int, void *, void *, void *);
extern void *get_particle_emitter_from_emitter_id(int);
extern void func_0004E888();
extern void func_0004E8B8();

static void func_0004CE30(WeakFx *e, void *param)
{
    int sheets[2][4] = {
        { SParticleSheetData_S_WEAKNESS_BASE, SParticleSheetData_S_WEAKNESS_PARTICLE,
          SParticleSheetData_S_WEAKNESS_FLARE, SParticleSheetData_S_WEAKNESS },
        { SParticleSheetData_S_TRIGGER_BASE, SParticleSheetData_S_TRIGGER_PARTICLE,
          SParticleSheetData_S_TRIGGER_FLARE, SParticleSheetData_S_TRIGGER },
    };
    int i;
    Emit *em;

    if (e->lws == 0) {
        AnimCls *cls;
        LightHdr *hdr;
        int j;
        e->lws = _SCRSetupLWS(ScriptAnimationObjDef_BOSS_WEAKNESS_LIGHT, param, ZeroPoint, IdentityQuaternion, 0);
        cls = GetScriptAnimationClass(e->lws);
        hdr = cls->hdr;
        for (j = 0; j < (cls->hdr)->n; j++) {
            if (cls->ents[j].id == 0) {
                { int off = j * 12; switch (*(int *)(hdr->types + off)) {
                case 0x1B:
                case 0x1C:
                case 0x21:
                case 0x22:
                case 0x23: {
                    int *l = cls->ents[j].ptr;
                    if (l != 0) {
                        SetGameLightUserParam(l, e);
                        SetGameLightUserFunc(l, func_0004E888);
                    }
                    break;
                }
                }}
            }
        }
        _SCRStartLWS(e->lws, -1, 5, 0);
    }
    for (i = 0; i < 4; i++) {
        int miss;
        em = &e->emit[i];
        if (em->id != 0)
            continue;
        if (e->kind == 0)
            miss = !chkBossWeakTexExist(e->tex);
        else
            miss = !chkBossTrigTexExist(e->tex);
        if (i == 0 && miss == 0)
            continue;
        em->id = boot_particle_emitter(get_particle_effect_id_from_sheet(sheets[e->kind][i]), param, func_0004E8B8, em);
        em->em = get_particle_emitter_from_emitter_id(em->id);
        em->flag = 1;
    }
}
