typedef struct {
    char pad0[8];
    int size;
    char padC[0x40 - 0xC];
} LoaderStat;

extern unsigned int strlen(const char *);
extern int iosSPrintf(char *, const char *, ...);
extern int LoaderSysGetstat(const char *, LoaderStat *);

static int func_000DDEF8(const char *name)
{
    LoaderStat st;
    char path[strlen(name) + 7];

    iosSPrintf(path, "host0:%s", name);
    LoaderSysGetstat(path, &st);
    return st.size;
}
