typedef struct {
    int w[7];
} ScriptControlButtonCallBack;

extern ScriptControlButtonCallBack D_00136AB8;

void InitScriptControlButtonCallBack(ScriptControlButtonCallBack *cb)
{
    *cb = D_00136AB8;
}
