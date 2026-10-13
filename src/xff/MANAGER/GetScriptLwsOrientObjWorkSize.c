extern int GetLwsOrientWorkSize();
extern int GetScriptObjWorkSize(int);

int GetScriptLwsOrientObjWorkSize(int arg0)
{
    int temp_s1;

    temp_s1 = GetLwsOrientWorkSize();
    return temp_s1 + GetScriptObjWorkSize(arg0 + 0x134);
}
