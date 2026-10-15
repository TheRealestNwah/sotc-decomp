typedef char *va_list;
#define va_start(ap, last) (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))
extern char B_00053B08[];
extern int vsprintf(char *, const char *, va_list);
extern void LoaderSysJumpRecoverPoint(char *);

void iosJumpRecoverPoint(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf(B_00053B08, fmt, ap);
    LoaderSysJumpRecoverPoint(B_00053B08);
}
