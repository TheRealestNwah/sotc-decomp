extern char *GetCharacterClass(void *obj);

void SetCharacterObjDemoCutFinishFlag(void *obj, int flag)
{
    GetCharacterClass(obj)[0x10A0] = flag;
}
