struct TexDrawEnv {
    unsigned long r[20];
};

extern int sceGsSetDefAlphaEnv(void *ap, short pabe);
extern int sceGsSyncPath(int mode, unsigned short timeout);
extern int sceGsPutDrawEnv(void *env);
extern struct TexDrawEnv D_001321A0;

void SetDrawEnvironment(int mode) {
    struct TexDrawEnv *env = (struct TexDrawEnv *)((unsigned int)&D_001321A0 | 0x20000000);

    sceGsSetDefAlphaEnv(&env->r[4], 0);
    switch (mode) {
    case 0:
        env->r[4] = 0x48;
        break;
    case 1:
        env->r[4] = 0x44;
        break;
    case 2:
        env->r[4] = 0x42;
        break;
    case 3:
        env->r[4] = 0x2800000064;
        break;
    case 4:
        env->r[4] = 0x68;
        break;
    }
    env->r[2] = 0x20000;
    env->r[3] = 0x47;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(env);
}
