extern unsigned int strlen(const char *);
extern char *strcpy(char *, const char *);
extern const char _ctype_[];
extern void iosDumpFVector(const char *, const char *, const char *, const float *);

void iosDumpMatrix(const char *prefix, const char *format, const char *suffix, const float *matrix)
{
    char prefixSpaces[0x100];
    char suffixSpaces[0x100];
    int i;
    const float *row;
    int prefixLength = strlen(prefix);
    int suffixLength = strlen(suffix);
    strcpy(prefixSpaces, prefix);
    strcpy(suffixSpaces, suffix);
    /* newlib isgraph: punctuation, letters and digits, excluding spaces. */
    for (i = 0; i < prefixLength; i++) {
        if ((_ctype_ + 1)[(unsigned)prefixSpaces[i]] & 0x17)
            prefixSpaces[i] = ' ';
    }
    for (i = 0; i < suffixLength; i++) {
        if ((_ctype_ + 1)[(unsigned)suffixSpaces[i]] & 0x17)
            suffixSpaces[i] = ' ';
    }
    for (i = 0, row = matrix; i < 4; i++, row += 4)
        iosDumpFVector(i == 0 ? prefix : prefixSpaces, format, i == 3 ? suffix : suffixSpaces, row);
}
