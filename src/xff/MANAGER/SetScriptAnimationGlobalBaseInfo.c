typedef struct {
    int words[11];
} ScriptAnimationGlobalBaseInfo;

extern ScriptAnimationGlobalBaseInfo info;

void SetScriptAnimationGlobalBaseInfo(ScriptAnimationGlobalBaseInfo *source)
{
    info = *source;
}
