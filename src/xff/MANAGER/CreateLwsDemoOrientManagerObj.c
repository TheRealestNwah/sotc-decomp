extern int GetScriptObjWorkSize(int *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysInitISYSLetterObj(void *);
extern void InitLwsDemoOrientManagerObj(void *, int *);
extern void isysSetObjImmediateDeleteFunc(void *, int);
extern void func_0007E8E8(void *);
extern void T_0007E978(void *);
void *CreateLwsDemoOrientManagerObj(void *heap, int extra, int *script)
{
    void *object;
    extra += GetScriptObjWorkSize(script);
    object = _isysCreateObj(heap, 0x1D, 0xC0, extra + 0x33, (int)T_0007E978, 16);
    if (object) {
        isysInitISYSLetterObj(object);
        InitLwsDemoOrientManagerObj(object, script);
        isysSetObjImmediateDeleteFunc(object, (int)func_0007E8E8);
    }
    return object;
}
