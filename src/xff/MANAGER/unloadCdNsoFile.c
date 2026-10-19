extern char B_001498C0[];
extern int sheetFileGetSize(void *);
extern void iosMallocSetExecGarbageCallback(int, int, int);
extern void isysRequestDeleteObj(void *);

void unloadCdNsoFile(void *a, void *b, char *obj)
{
    if (obj != 0) {
        int size = sheetFileGetSize(a);
        char *m = B_001498C0;

        *(int *)(m + 0x18) -= size;
        iosMallocSetExecGarbageCallback(*(int *)(obj + 0x1C), -1, 0);
        isysRequestDeleteObj(obj);
    }
}
