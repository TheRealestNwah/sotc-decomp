extern int strncmp(const char *s1, const char *s2, unsigned int n);
extern char D_0013A000[];

char *checkHookDesc(char *desc) {
    return strncmp(desc, D_0013A000, 6) == 0 ? desc + 6 : 0;
}
