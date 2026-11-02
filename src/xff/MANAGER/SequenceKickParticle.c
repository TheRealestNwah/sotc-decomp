extern unsigned char *CreateSubLinkObjByGeometryPointer(char *, int);
extern int boot_particle_emitter(int, char *, void *, unsigned char *);
extern void isysRequestDeleteObj(void *);
extern void SetSubLinkObjDeleteFuncInfo(unsigned char *, int, void *, int);
extern void func_000EE510(void *, int *);
extern void T_000EE558(void *);

typedef struct ParticleKickInfo {
    int emitter;
    int particle;
} ParticleKickInfo;

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
