typedef char *va_list;
#define va_start(ap, last) \
    (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

typedef struct {
    char pad0[0x40];
} KPrintfContext3D;

extern int iosInitKPrintfContext3D(KPrintfContext3D *, float *, int, int, float, float, float, float);
extern int vsprintf(char *, const char *, va_list);
extern void kprintfContextCentering(KPrintfContext3D *, char *);

void DebugPrintf3D(float *pos, const char *fmt, ...)
{
    KPrintfContext3D ctx;
    char buf[0x100];
    va_list ap;

    if (iosInitKPrintfContext3D(&ctx, pos, 0, 1, 0.5f, 0.75f, 1.0f, 1.0f) != 0) {
        va_start(ap, fmt);
        vsprintf(buf, fmt, ap);
        kprintfContextCentering(&ctx, buf);
    }
}
