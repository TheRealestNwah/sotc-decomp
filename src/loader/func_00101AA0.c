extern void LoaderSysJumpRecoverPoint(const char *message, void *at);
extern char D_001363A8[];

void func_00101AA0(void) {
    register char *ra asm("$31");

    LoaderSysJumpRecoverPoint(D_001363A8, ra - 8);
}
