extern void func_00030D50();
extern void *createScriptObj(void *, int, int, int, int, int, int, int);

void *CreateWindThread(int a, int b)
{
    return createScriptObj(func_00030D50, a, b, 0x1000, 0, 1, 0, 0);
}
