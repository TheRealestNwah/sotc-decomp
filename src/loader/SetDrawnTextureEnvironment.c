struct TexDrawEnv {
    unsigned long r[20];
};

extern int sceGsSetDefTexEnv(void *tp, short flush, short tbp0, short tbw, short psm, short w,
                              short h, short tfx, short cbp, short cpsm, short cld, short func);
extern int sceGsSetDefAlphaEnv(void *ap, short pabe);
extern int sceGsSyncPath(int mode, unsigned short timeout);
extern int sceGsPutDrawEnv(void *env);
extern struct TexDrawEnv D_00132100;
extern int D_0013A130;

void SetDrawnTextureEnvironment(int tbp) {
    struct TexDrawEnv *env = (struct TexDrawEnv *)((unsigned int)&D_00132100 | 0x20000000);

    sceGsSetDefTexEnv(&env->r[12], 0, tbp, D_0013A130 / 64, 0, 10, 8, 0, 0, 0, 0, 1);
    sceGsSetDefAlphaEnv(&env->r[4], 0);
    env->r[4] = 0x44;
    env->r[2] = 0x20000;
    env->r[3] = 0x47;
    env->r[14] = 0x61;
    env->r[18] = 0;
    env->r[10] = 0;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(env);
}
