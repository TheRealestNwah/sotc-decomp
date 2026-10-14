extern void iosSetKPrintfColorContext(char *, int, float, float, float, float);

extern void kprintfContext(signed char *, void *, int);
extern unsigned char RO_0017C100[];
extern unsigned char RO_0017C108[];

void DebugDispItem(signed char *arg0, int arg1, int arg2) {
    iosSetKPrintfColorContext(arg0, 0, 1.0f, 1.0f, 1.0f, 1.0f);
    kprintfContext(arg0, RO_0017C100, arg1);
    iosSetKPrintfColorContext(arg0, 0, 0.25f, 0.75f, 1.0f, 1.0f);
    kprintfContext(arg0, RO_0017C108, arg2);
}
