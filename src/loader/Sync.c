struct TexDrawEnv {
    unsigned long r[20];
};

extern int FlushCache(int op);
extern int sceGsSyncPath(int mode, unsigned short timeout);
extern int sceGsSyncV(int mode);
extern void sceGsSwapDBuff(void *db, int id);
extern void sceGsSetHalfOffset(void *draw, short centerx, short centery, short halfoff);
extern int sceGsSetDefAlphaEnv(void *ap, short pabe);
extern int sceGsPutDrawEnv(void *env);
extern char D_0013EB60[];
extern struct TexDrawEnv D_001321A0;
extern int D_0013A13C;
extern int D_0013A140;
extern int D_0013A138;

static inline void restoreNormalDrawEnvironment(void *db, int field, int halfoff) {
    char *env = (char *)((unsigned int)db | 0x20000000);

    if (field) {
        sceGsSetHalfOffset(env + 0x150, 0x800, 0x800, halfoff);
        sceGsPutDrawEnv(env + 0x140);
    } else {
        sceGsSetHalfOffset(env + 0x60, 0x800, 0x800, halfoff);
        sceGsPutDrawEnv(env + 0x50);
    }
}

static inline void setDrawEnvironment(int mode) {
    struct TexDrawEnv *env = (struct TexDrawEnv *)((unsigned int)&D_001321A0 | 0x20000000);

    sceGsSetDefAlphaEnv(&env->r[4], 0);
    switch (mode) {
    case 0:
        env->r[4] = 0x48;
        break;
    case 1:
        env->r[4] = 0x44;
        break;
    }
    env->r[2] = 0x20000;
    env->r[3] = 0x47;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(env);
}

void Sync(void) {
    FlushCache(0);
    sceGsSyncPath(1, 0);
    D_0013A140 = sceGsSyncV(0);
    D_0013A13C++;
    D_0013A138 = D_0013A13C & 1;
    sceGsSwapDBuff(D_0013EB60, D_0013A138);
    restoreNormalDrawEnvironment(D_0013EB60, D_0013A138, D_0013A140);
    setDrawEnvironment(1);
}
