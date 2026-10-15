extern int strlen(const char *);

char *DEBUG_get_base_name(char *s)
{
    int i;
    for (i = strlen(s) - 2; i != -1; i--) {
        if (s[i] == '/')
            return s + i + 1;
    }
    return s;
}
