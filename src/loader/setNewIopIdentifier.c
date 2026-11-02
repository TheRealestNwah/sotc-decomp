extern int LoaderSysPrintf(const char *format, ...);
extern unsigned int strlen(const char *s);
extern char *strncpy(char *dst, const char *src, unsigned int n);
extern char D_00136980[];
extern int D_0013A008;
extern char D_0013CB90[][16];

char *setNewIopIdentifier(const char *name) {
    char *slot;

    LoaderSysPrintf(D_00136980, name, D_0013A008);
    slot = D_0013CB90[D_0013A008++];
    return strncpy(slot, name, strlen(name));
}
