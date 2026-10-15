extern int GetScriptObjWorkSize(void *);

int GetScriptSpriteObjWorkSize(char *p)
{
    int n = *(int *)(p + 8) * 135 + 0x43;
    return n + GetScriptObjWorkSize(p + 0x3C);
}
