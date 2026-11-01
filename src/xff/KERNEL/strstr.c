typedef unsigned int size_t;

char *strstr(const char *searchstring, const char *compare)
{
    if (*searchstring == 0) {
        if (*compare) {
            return (char *)0;
        }
        return (char *)searchstring;
    }

    while (*searchstring) {
        size_t i;
        i = 0;

        while (1) {
            if (compare[i] == 0) {
                return (char *)searchstring;
            }

            if (compare[i] != searchstring[i]) {
                break;
            }
            i++;
        }
        searchstring++;
    }

    return (char *)0;
}
