typedef char *va_list;
#define va_start(ap, last) \
    (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

struct RecoverReg {
    int lo;
    int hi;
};

extern void LoaderSysExecuteRecoveryFirstProcess(void);
extern int vsprintf(char *buf, const char *format, va_list ap);
extern void func_00100A58(void);
extern char D_0013B348[];
extern char D_00100CD0[];
extern struct RecoverReg D_00131D80[64];
register char *gp asm("$28");

void LoaderSysJumpRecoverPoint(const char *format, ...) {
    register char *ra asm("$31");
    register char *sp asm("$29");
    va_list ap;
    void *pc;
    char *savedRa;
    int i;

    __asm__("la %0, _gp" : "=r"(gp));
recover:
    LoaderSysExecuteRecoveryFirstProcess();
    va_start(ap, format);
    vsprintf(D_0013B348, format, ap);
    pc = D_00100CD0;
    savedRa = ra;
    for (i = 63; i >= 0; i--) {
        D_00131D80[i].lo = 0;
    }
    D_00131D80[46].lo = (int)pc;
    D_00131D80[31].lo = (int)savedRa;
    D_00131D80[29].lo = (int)sp;
    func_00100A58();
}
