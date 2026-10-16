extern void *GetCharacterClass(void *obj);

int GetCharacterObjMotionShiftCallBackMaxEntry(void *obj)
{
    char *c = GetCharacterClass(obj);

    if (c == 0) {
        return -1;
    }
    return *(int *)(c + 0x2C8);
}
