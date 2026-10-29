typedef char *va_list;
#define va_start(ap, last)     (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

typedef struct {
    int enabled;
} KPrintState;

extern KPrintState D_001359F0;
extern char B_001482A8[];
extern int iosGetFontIDWithEUC(int);
extern int iosGetFontIDWithSJIS(int);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern int vsprintf(char *, const char *, va_list);
extern void func_00015310(void *, char *, int (*)(int));

void kprintfContextSJIS(void *ctx, const char *fmt, ...)
{
    va_list ap;

    if (D_001359F0.enabled) {
        iosDlPushLayer(*(int *)((char *)ctx + 0x38));
        va_start(ap, fmt);
        vsprintf(B_001482A8, fmt, ap);
        func_00015310(ctx, B_001482A8, iosGetFontIDWithSJIS);
        iosDlPopLayer();
    }
}
