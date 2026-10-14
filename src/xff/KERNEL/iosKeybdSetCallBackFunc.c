extern int D_00040FBC;
extern int D_00040FC0;

int iosKeybdSetCallBackFunc(int f)
{
    if (D_00040FBC == 0) {
        return 0;
    }
    D_00040FC0 = f;
    return 1;
}
