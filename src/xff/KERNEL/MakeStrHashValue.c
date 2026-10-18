extern int strcmp(const char *, const char *);
extern unsigned int strlen(const char *);
int MakeStrHashValue(const char *string)
{
    int value = 0;
    int parity;
    unsigned int offset;
    if (!string || strcmp("NULL", string) == 0)
        return 0;
    for (parity = 0; parity < 2; parity++)
        for (offset = parity; offset < strlen(string); offset += 2) {
            int product = value * 77;
            int character = (signed char)string[offset] - 45;
            value = product + character;
        }
    return value;
}