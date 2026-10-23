typedef struct { int sp, base, a, start, end, size; } Env;
extern char rootPtn[];
extern void *iosMallocAlign(int, int, int);
extern void iosFree(int);
extern int isysSearchModuleFuncNameByAddr(char *, char *, int);

void isysDumpSubThreadStatus(unsigned char *o)
{
    Env *e;
    char *moduleName;
    char *functionName;
    switch (o[8]) {
    case 6:
    case 9:
    case 11:
    case 12:
    case 13:
    case 14:
    case 22:
    case 29:
    case 33:
        e = (Env *)(o + 0x20);
        break;
    case 7:
    case 8:
    case 10:
    case 15 ... 21:
    case 23 ... 28:
    case 30 ... 32:
        e = 0;
        break;
    default:
        e = 0;
        break;
    }
    moduleName = iosMallocAlign((int)rootPtn, 0x100, 4);
    functionName = iosMallocAlign((int)rootPtn, 0x100, 4);
    isysSearchModuleFuncNameByAddr(moduleName, functionName, e->sp);
    iosFree((int)functionName);
    iosFree((int)moduleName);
}
