typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern char B_001498C0[];
extern void *iosMallocAlign(Ptn *, int, int);
extern void sheetFileRead(void *, void *, int);
extern char *isysGetXffEntryPointPreRelocation(void *);
extern int texGetWorkSize(char *);
extern void *isysCreateModuleObjExisted(void *, int, void *, int, int, int, void *);
extern void texInitialize(char *, char *);
extern void windowSetTex(int);
static inline char *objectManagerStats(void) { return B_001498C0; }
void *loadCdWinTexFile(void *file, int unused, int size)
{
    char *object = 0;
    char *buffer = iosMallocAlign(&rootPtn, size, 16);
    if (buffer) {
        int workSize;
        sheetFileRead(file, buffer, size);
        workSize = texGetWorkSize(isysGetXffEntryPointPreRelocation(buffer));
        object = isysCreateModuleObjExisted(buffer, workSize, &rootPtn, 1, 0, 1, &rootPtn);
        if (object) {
            *(unsigned int *)(objectManagerStats() + 0x1C) += (unsigned int)size;
            texInitialize(object, 0);
            windowSetTex((int)object);
        }
    }
    return object;
}
