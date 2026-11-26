extern unsigned char *CreateSubLinkObjByGeometryPointer(char *, int);
extern int boot_particle_emitter(int, char *, void *, unsigned char *);
extern void isysRequestDeleteObj(void *);
extern void SetSubLinkObjDeleteFuncInfo(unsigned char *, int, void *, int);
typedef struct ParticleKickInfo {
    int emitter;
    int particle;
} ParticleKickInfo;
extern char *GetSubLinkClass(unsigned char *object);
typedef struct {
    int id;
    void *emitter;
} EmitterRef;
extern void stop_particle_emitter_callback(void *, int);
extern void end_particle_emitter(void *, int, int);
extern void stop_particle_emitter_geometry_pointer_reference(void *, int);

static void func_000EE510(void *obj, EmitterRef *r);
static void T_000EE558(void *obj);

unsigned char *SequenceKickParticle(int particle, char *geometry)
{
    unsigned char *link;
    ParticleKickInfo info;
    ParticleKickInfo tmp;

    link = CreateSubLinkObjByGeometryPointer(geometry, 8);
    if (link != 0) {
        tmp.emitter = boot_particle_emitter(particle, geometry, T_000EE558, link);
        tmp.particle = particle;
        info = tmp;
        if (info.emitter != -1) {
            if (info.emitter == 0) {
                isysRequestDeleteObj(link);
                link = 0;
            } else {
                SetSubLinkObjDeleteFuncInfo(link, (int)func_000EE510, &info, 8);
            }
        } else {
            link = 0;
        }
    }
    return link;
}

int KickParticleGetResourceId(unsigned char *object)
{
    return **(int **)(GetSubLinkClass(object) + 0x10);
}

static void func_000EE510(void *obj, EmitterRef *r)
{
    stop_particle_emitter_callback(r->emitter, r->id);
    end_particle_emitter(r->emitter, r->id, 1);
    stop_particle_emitter_geometry_pointer_reference(r->emitter, r->id);
}

static void T_000EE558(void *obj)
{
    isysRequestDeleteObj(obj);
}
