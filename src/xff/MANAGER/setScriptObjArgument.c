extern char *GetScriptClass();

void setScriptObjArgument(int a, int b)
{
    *(int *)(GetScriptClass(a) + 0x24) = b;
}
