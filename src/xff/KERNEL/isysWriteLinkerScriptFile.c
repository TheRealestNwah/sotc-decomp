extern char RO_00042A48[];
extern void iosSPrintf(char *, const char *, ...);
extern void printf();
extern void OutputLinkerScriptFile(void *, char *, void *);

void isysWriteLinkerScriptFile(char *m)
{
    char buf[0x400];
    void *o = *(void **)(m + 0x1C);
    iosSPrintf(buf, RO_00042A48, *(int *)(m + 0x38));
    OutputLinkerScriptFile(o, buf, printf);
}
