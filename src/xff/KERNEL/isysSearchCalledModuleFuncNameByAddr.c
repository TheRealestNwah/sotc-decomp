extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern char executableModuleGroup[];
extern int func_0000AC30(char *, char *, void *, unsigned int);
int isysSearchCalledModuleFuncNameByAddr(char *module_name, char *function_name, unsigned int address)
{
    void *object = 0;
    void **link;
    int found = 0;
    int result;
    for (link = isysGroupForFirst(executableModuleGroup, 0); link != 0;
         link = isysGroupForNext(link, 0)) {
        object = *link;
        result = func_0000AC30(module_name, function_name, object, address);
        if (result) {
            found = result;
            break;
        }
    }
    if (object)
        isysGroupForExit(object, 0);
    return found;
}
