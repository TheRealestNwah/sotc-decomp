extern void charrootdyn_updateCharacterClassParentGeometry(int, void *, int);
extern void func_0005CD18(int, int);
extern unsigned char ZeroPoint[];

void motrootdyn_startfreefall(int arg0, int arg1)
{
    charrootdyn_updateCharacterClassParentGeometry(arg1, ZeroPoint, arg1 + 0x6D0);
    func_0005CD18(arg0, arg1);
}
