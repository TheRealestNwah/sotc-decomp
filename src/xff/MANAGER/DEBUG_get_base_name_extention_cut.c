extern char *strrchr(const char *, int);
extern unsigned int strlen(const char *);
char *DEBUG_get_base_name_extention_cut(char *path)
{
    char *extension = strrchr(path, '.');
    int index;
    if (extension)
        *extension = 0;
    for (index = strlen(path) - 2; index != -1; index--) {
        if (path[index] == '/')
            return path + index + 1;
    }
    return path;
}