typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *GetCharacterClass(int);
extern void _resetBaseMoveWork(int a, char *p);
extern void func_001038E8(char *);
extern void func_00103830(char *);

static void func_001037C0(int obj, char *w)
{
    char *c = GetCharacterClass(obj);
    s128 v = (*(Vec4 **)(c + 0x13C))->q;

    *(int *)(w + 0x34) = 1;
    ((Vec4 *)(w + 0x250))->q = v;
    *(int *)(w + 0x38) = 1;
    *(int *)(w + 0x3C) = 0;
    *(int *)(w + 0x30) = 0;
    *(int *)(w + 0x154) = 0;
    _resetBaseMoveWork(obj, w);
    func_001038E8(w);
    func_00103830(w);
}
