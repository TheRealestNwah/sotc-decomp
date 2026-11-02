extern char *GetCharacterClass(void *);
extern void func_00066578(void *, void *, void *, float, float);
extern void regularizeMatAry(void *, int);
extern void CopyMultiQuaternion(void *, void *, int);

void CalcRootFitting(void *object, void *arg1, void *arg2, float arg3, float arg4)
{
    char *character = GetCharacterClass(object);
    int count = 0;
    int *flags;
    char *root;

    *(int *)(character + 0x113C) = 0;
    flags = *(int **)(character + 0x33C);
    if (*(char **)(character + 0x358) != 0) {
        count = *(int *)(*(char **)(character + 0x358) + 0x20);
    }
    while (count-- != 0) {
        *flags++ = 0;
    }
    if ((*(unsigned int *)(*(char **)(character + 0x1140) + 0x38) >> 5) & 1) {
        func_00066578(object, arg1, arg2, arg3, arg4);
        return;
    }
    root = GetCharacterClass(object);
    regularizeMatAry(*(void **)(root + 0x2DC), *(short *)(root + 0x1B4));
    CopyMultiQuaternion(*(void **)(root + 0x2E8), *(void **)(root + 0x2DC), *(short *)(root + 0x1B4));
}
