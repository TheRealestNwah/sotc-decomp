extern void func_0003FF78(void);
extern void func_0003F860(int **, void *, void *);
extern void *_isysCreateObj(void *, int, int, int, void (*)(void), int);

void *CreateAnimationDefObj(void *grp, int size, int **res)
{
    void *o = _isysCreateObj(grp, 0x12, 0x38, *(int *)(*(char **)((char *)*res + 0x20) + 0x14) * 12 + size + 0x43, func_0003FF78, 0x10);

    func_0003F860(res, o, grp);
    return o;
}
