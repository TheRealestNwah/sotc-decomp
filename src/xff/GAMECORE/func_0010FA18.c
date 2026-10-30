extern int _resetBaseMoveWork(int a, char *p);
extern void func_0010FA88(char *);
extern char *GetCharacterClass(int);

static void func_0010FA18(int obj, char *w)
{
    _resetBaseMoveWork(obj, w);
    *(int *)(w + 0x30) = 0;
    *(float *)(w + 0x40) = 1.0f;
    *(int *)(w + 0x9C) = 0;
    *(int *)(w + 0x34) = 0;
    *(int *)(w + 0x74) = 0;
    *(int *)(w + 0x78) = 0;
    *(int *)(w + 0x3C) = 0;
    func_0010FA88(w);
    *(int *)(w + 0x98) = *(signed char *)(GetCharacterClass(obj) + 0x363);
}
