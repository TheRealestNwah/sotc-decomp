typedef struct { char pad[0x1C]; int used; } TexMan;
extern TexMan B_001498C0;
extern int sheetFileGetSize(void *);
extern void texDelete(void *);
extern void iosMallocSetExecGarbageCallback(int, int, int);
extern void isysRequestDeleteObj(void *);

void unloadCdNtoFile(void *f, int b, char *o)
{
    if (o == 0)
        return;
    B_001498C0.used -= sheetFileGetSize(f);
    texDelete(o);
    iosMallocSetExecGarbageCallback(*(int *)(o + 0x1C), -1, 0);
    isysRequestDeleteObj(o);
}
