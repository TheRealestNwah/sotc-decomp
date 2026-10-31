typedef char *va_list;
#define va_start(ap, last)     (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))
extern int vsprintf(char *, const char *, va_list);
extern int strlen(const char *);
extern void LoaderSysPrintf(const char *, ...);
extern void LoaderSysFWrite(int, const char *, int);

static int func_00002F80(int fd, const char *fmt, ...)
{
    char buf[256];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    if (fd < 0) {
        LoaderSysPrintf("%s", buf);
    } else {
        LoaderSysFWrite(fd, buf, strlen(buf));
    }
    return strlen(buf);
}
