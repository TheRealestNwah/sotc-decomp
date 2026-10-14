extern int isysGetSubThreadWorkSize();

int GetScriptObjWorkSize(int *p)
{
    return isysGetSubThreadWorkSize(p[2]);
}
