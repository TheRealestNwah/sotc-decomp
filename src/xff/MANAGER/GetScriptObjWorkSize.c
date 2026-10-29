extern int isysGetSubThreadWorkSize(int);

int GetScriptObjWorkSize(int *p)
{
    return isysGetSubThreadWorkSize(p[2]);
}
