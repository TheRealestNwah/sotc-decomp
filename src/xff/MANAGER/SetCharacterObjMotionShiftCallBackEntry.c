extern void *GetCharacterClass(void *);
int SetCharacterObjMotionShiftCallBackEntry(void *object, int index, int id, int entry, int leave, int arg)
{
    char *character = GetCharacterClass(object);
    if (character) {
        int *element = (int *)(index * 16 + (int)*(char **)(character + 0x2CC));
        element[0] = id;
        element[1] = entry;
        element[2] = leave;
        element[3] = arg;
        return 0;
    }
    return -1;
}
