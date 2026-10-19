typedef struct { char pad[0x1C]; int size; } BinarySize;
extern BinarySize B_001498C0;
extern int sheetFileGetSize(void *);
extern void isysRequestDeleteObj(void *);

void unloadCdWinTexFile(void *a, int b, void *obj)
{
    if (obj != 0) {
        B_001498C0.size -= sheetFileGetSize(a);
        isysRequestDeleteObj(obj);
    }
}
