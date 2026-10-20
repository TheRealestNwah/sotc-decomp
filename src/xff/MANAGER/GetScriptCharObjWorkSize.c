extern int GetCharacterObjWorkSize(void *);
extern int GetScriptObjWorkSize(int *);

int GetScriptCharObjWorkSize(unsigned char *def)
{
    int work = GetCharacterObjWorkSize(def);
    return work + GetScriptObjWorkSize((int *)(def + 0x11C));
}