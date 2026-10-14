extern int GetGeometryPointerObject(int);
extern int GetLayoutClass(int);

int AI_PlayerParentFlag(int arg0, int arg1)
{
    return GetGeometryPointerObject(GetLayoutClass(arg1) + 0xC0) == arg0;
}
