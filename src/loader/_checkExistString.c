extern int strcmp(const char *s1, const char *s2);

int _checkExistString(const char *s, const char **list) {
    int i;

    for (i = 0; list[i] != 0; i++) {
        if (strcmp(list[i], s) == 0) {
            return 1;
        }
    }
    return 0;
}
