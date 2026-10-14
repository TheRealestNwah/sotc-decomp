extern int D_00040FC4;
extern int D_00040FC8;

int iosMouseSetCallBackFunc(int f)
{
    if (D_00040FC4 == 0) {
        return 0;
    }
    D_00040FC8 = f;
    return 1;
}
