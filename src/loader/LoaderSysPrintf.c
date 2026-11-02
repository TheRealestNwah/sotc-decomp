typedef char *va_list;
#define va_start(ap, last) \
    (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern int vsprintf(char *buf, const char *format, va_list ap);
extern int printf(const char *format, ...);
extern unsigned int strlen(const char *s);

int LoaderSysPrintf(const char *format, ...) {
    char buf[256];
    va_list ap;

    va_start(ap, format);
    vsprintf(buf, format, ap);
    printf(buf);
    return strlen(buf);
}
