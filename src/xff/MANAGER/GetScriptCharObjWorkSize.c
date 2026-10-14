extern int GetCharacterObjWorkSize();
extern int GetScriptObjWorkSize(int);

int GetScriptCharObjWorkSize(int arg0)
{
    int temp_s1;

    temp_s1 = GetCharacterObjWorkSize();
    return temp_s1 + GetScriptObjWorkSize(arg0 + 0x11C);
}
