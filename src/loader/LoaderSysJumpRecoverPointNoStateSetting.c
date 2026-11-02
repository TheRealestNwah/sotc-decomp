typedef char *va_list;
#define va_start(ap, last) \
    (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern void LoaderSysExecuteRecoveryFirstProcess(void);
extern int vsprintf(char *buf, const char *format, va_list ap);
extern void func_00100A58(void);
extern char D_0013B348[];
register char *gp asm("$28");

void LoaderSysJumpRecoverPointNoStateSetting(const char *format, ...) {
    va_list ap;

    __asm__("la %0, _gp" : "=r"(gp));
    LoaderSysExecuteRecoveryFirstProcess();
    va_start(ap, format);
    vsprintf(D_0013B348, format, ap);
    func_00100A58();
}
