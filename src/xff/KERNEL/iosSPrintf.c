typedef char *va_list;
#define va_start(ap, last) \
    (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern int vsprintf(char *, const char *, va_list);

int iosSPrintf(char *buf, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    return vsprintf(buf, fmt, ap);
}
