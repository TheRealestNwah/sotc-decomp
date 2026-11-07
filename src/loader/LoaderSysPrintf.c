typedef char *va_list;
#define va_start(ap, last) \
    (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern int vsprintf(char *buf, const char *format, va_list ap);
extern int printf(const char *format, ...);
extern unsigned int strlen(const char *s);
extern char D_00136A20[];
extern char D_00136A68[];
extern char D_00136AB0[];
extern int D_0013A008;
extern char D_0013CB90[][16];

int LoaderSysPrintf(const char *format, ...) {
    char buf[256];
    va_list ap;

    va_start(ap, format);
    vsprintf(buf, format, ap);
    printf(buf);
    return strlen(buf);
}

/* Kept after LoaderSysPrintf: with only a prototype in scope, gcc fills the loop
   guard as blezl instead of the Original's blez. */
void LoaderSysDumpIopModuleIdentifiers(void) {
    int i;

    LoaderSysPrintf(D_00136A20);
    LoaderSysPrintf(D_00136A68);
    for (i = 0; i < D_0013A008; i++) {
        LoaderSysPrintf(D_00136AB0, i, D_0013CB90[i]);
    }
    LoaderSysPrintf(D_00136A68);
}
