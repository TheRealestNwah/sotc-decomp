typedef char *va_list;
#define va_start(ap, last) \
    (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern int vsprintf(char *, const char *, va_list);
extern void usbSerialSysPutString(char *);

void iosUsbSerialPrintf(const char *fmt, ...)
{
    char buf[0x100];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    usbSerialSysPutString(buf);
}
