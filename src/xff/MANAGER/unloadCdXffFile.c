typedef struct { char pad[0x28]; int size; } BinarySize;
extern BinarySize B_001498C0;
extern int sheetFileGetSize(void *);
extern void isysRequestDeleteObj(void *);

void unloadCdXffFile(void *a, int b, void *obj)
{
    int s = sheetFileGetSize(a);
    B_001498C0.size -= s;
    if (obj != 0)
        isysRequestDeleteObj(obj);
}
