extern int GetLwsOrientWorkSize(void *);
extern int GetScriptObjWorkSize(int *);
int GetScriptLwsOrientObjWorkSize(unsigned char *def)
{
    int work = GetLwsOrientWorkSize(def);
    return work + GetScriptObjWorkSize((int *)(def + 0x134));
}