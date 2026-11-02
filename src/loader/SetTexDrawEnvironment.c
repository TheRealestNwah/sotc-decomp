struct DrawEnv {
    char unk0[0x10];
    unsigned long frame1;
    char unk18[8];
    unsigned long zbuf1;
};

extern void sceGsSetDefDrawEnv(void *env, short psm, short w, short h, short ztest, short zpsm);
extern void sceGsSyncPath(int mode, unsigned short timeout);
extern void sceGsPutDrawEnv(void *env);
extern struct DrawEnv D_00132070;
extern int D_0013A130;
extern int D_0013A134;

void SetTexDrawEnvironment(int fbp) {
    struct DrawEnv *env = (struct DrawEnv *)((unsigned int)&D_00132070 | 0x20000000);

    sceGsSetDefDrawEnv(&env->frame1, 0, D_0013A130, D_0013A134, 1, 0x31);
    fbp = fbp / 32 & 0x1FF;
    env->frame1 = (env->frame1 & ~0x1FF) | fbp;
    env->zbuf1 |= 0x100000000;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(env);
}
