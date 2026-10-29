extern int GetLayoutObjWorkSize(void *);
extern int GetScriptObjWorkSize(int);

int GetScriptLayoutObjWorkSize(int arg0)
{
    int temp_s1;

    temp_s1 = GetLayoutObjWorkSize((void *)arg0);
    return temp_s1 + GetScriptObjWorkSize(arg0 + 0x7C);
}
