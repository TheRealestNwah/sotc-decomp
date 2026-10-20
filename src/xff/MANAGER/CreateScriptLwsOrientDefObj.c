extern void func_00092988(void);
extern void func_00092388(int **, void *, void *);
extern int GetLwsOrientNodeNum(int);
extern void *_isysCreateObj(void *, int, int, int, int, int);

void *CreateScriptLwsOrientDefObj(void *grp, int size, int **res)
{
    int n = GetLwsOrientNodeNum(*(int *)((char *)*res + 0x20)) * 12 + 0x33;
    void *o = _isysCreateObj(grp, 0x17, 0x80, size + n, (int)func_00092988, 0x10);

    func_00092388(res, o, grp);
    return o;
}
