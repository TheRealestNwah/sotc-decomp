extern void *DldSysUndefSymbol;
typedef struct {
    int kind;
    char rest[44];
} ControlDefinition;
extern int func_0004E5F8(void *, ControlDefinition *);
static inline ControlDefinition *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return (ControlDefinition *)(data + index * *(int *)(definition + 0xC));
    }
    return 0;
}
static inline int checkDefinitions(void *status, ControlDefinition *entry)
{
    int result;
    while (entry->kind != 1) {
        result = func_0004E5F8(status, entry++);
        if (result == 0)
            goto done;
    }
    result = 1;
done:
    return result;
}
int CheckControlDefByStatus(void *status, unsigned int *reference)
{
    return checkDefinitions(status, resourceData(reference));
}