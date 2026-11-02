extern int WaitSema(int sema_id);
extern void PutStringS(int attr, const char *format, ...);
extern int sceDevctl(const char *name, int cmd, void *arg, unsigned int arglen, void *buf,
                     unsigned int buflen);
extern int sceCdPowerOff(int *stat);
extern int D_0013A118;
extern void (*D_0013A11C)(void);
extern char D_0013A120[];
extern char D_0013A128[];
extern char D_001373F0[];

void func_00104FF0(void) {
    int stat;

    while (1) {
        WaitSema(D_0013A118);
        if (D_0013A11C) {
            D_0013A11C();
        }
        PutStringS(0x4080FF80, D_001373F0);
        sceDevctl(D_0013A120, 0x5003, 0, 0, 0, 0);
        while (sceDevctl(D_0013A128, 0x4402, 0, 0, 0, 0) < 0) {
        }
        while (!sceCdPowerOff(&stat) || stat) {
        }
    }
}
