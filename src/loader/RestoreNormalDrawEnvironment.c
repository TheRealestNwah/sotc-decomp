extern void sceGsSetHalfOffset(void *draw, short centerx, short centery, short halfoff);
extern void sceGsPutDrawEnv(void *env);

void RestoreNormalDrawEnvironment(void *db, int field, int halfoff) {
    char *env = (char *)((unsigned int)db | 0x20000000);

    if (field) {
        sceGsSetHalfOffset(env + 0x150, 0x800, 0x800, halfoff);
        sceGsPutDrawEnv(env + 0x140);
    } else {
        sceGsSetHalfOffset(env + 0x60, 0x800, 0x800, halfoff);
        sceGsPutDrawEnv(env + 0x50);
    }
}
