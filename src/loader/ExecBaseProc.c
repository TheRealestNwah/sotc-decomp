struct TexDrawEnv {
    unsigned long r[20];
};

extern int sceGsSetDefAlphaEnv(void *ap, short pabe);
extern int sceGsSyncPath(int mode, unsigned short timeout);
extern int sceGsPutDrawEnv(void *env);
extern void func_001059D8(void);
extern struct TexDrawEnv D_001321A0;

void ExecBaseProc(void) {
    struct TexDrawEnv *env = (struct TexDrawEnv *)((unsigned int)&D_001321A0 | 0x20000000);

    sceGsSetDefAlphaEnv(&env->r[4], 0);
    env->r[4] = 0x48;
    env->r[2] = 0x20000;
    env->r[3] = 0x47;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(env);
    func_001059D8();
}
