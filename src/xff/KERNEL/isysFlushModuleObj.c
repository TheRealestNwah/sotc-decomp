extern void iosFree(void *);
static void func_00008108(void *);
int isysFlushModuleObj(char *object)
{
    char *module;
    char *entry;
    char *state;
    int count;
    if (*(int *)(object + 0x2C) & 0x40000000) {
        iosFree(*(void **)(*(char **)(object + 0x1C) + 4));
        func_00008108(object);
    } else {
        state = object + 0x30;
        if (*(void **)(state + 4) != 0) {
            iosFree(*(void **)(state + 4));
            *(int *)state = 0;
        }
        func_00008108(object);
        module = *(char **)(object + 0x1C);
        if (module != 0) {
            count = *(int *)(module + 0x40) - 2;
            entry = *(char **)(module + 0x30) + 0x20;
            while (count != -1) {
                if (*(int *)(entry + 0x18) != 0) {
                    *(int *)(entry + 0x18) = 0;
                    iosFree(*(void **)entry);
                }
                count--;
                entry += 0x20;
            }
            iosFree(module);
        }
    }
    return 0;
}
