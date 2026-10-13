extern void CopyGeometryPointer(int, int);
extern void *GetCharacterClass();

void ChangeCharacterObjControlledTarget(int arg0, int arg1, int arg2, int arg3)
{
    void *temp_v0;

    temp_v0 = GetCharacterClass();
    (*(int *)((char *)(temp_v0) + 0x960)) = arg1;
    if (arg0 != arg1) {
        (*(signed char *)((char *)(temp_v0) + 0x9C5)) = 1;
        CopyGeometryPointer(temp_v0 + 0x970, arg2);
        (*(int *)((char *)(temp_v0) + 0x9B0)) = arg3;
    }
}
