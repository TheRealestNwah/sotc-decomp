extern int GetClothWorkSize(char *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern int InitAliasLayoutObj(unsigned char *, int *, unsigned char *);
extern void isysSetObjImmediateDeleteFunc(void *, int);
static int T_00078520(unsigned char *);
static void T_00078508(unsigned char *);

unsigned char *CreateAliasLayoutObj(void *heap, int extra, int *definition, unsigned char *parent)
{
    int clothSize = 0;
    unsigned char *object;

    if (definition[3]) {
        char *module = *(char **)(definition[3] + 8);
        clothSize = GetClothWorkSize(*(char **)(module + 0x20));
    }
    object = _isysCreateObj(heap, 10, 0x1E0, extra + clothSize, (int)T_00078520, 16);
    if (object) {
        InitAliasLayoutObj(object, definition, parent);
        isysSetObjImmediateDeleteFunc(object, (int)T_00078508);
    }
    return object;
}
