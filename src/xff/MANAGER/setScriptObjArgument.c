extern void *GetScriptClass(unsigned char *);
void setScriptObjArgument(unsigned char *object, int argument)
{
    *(int *)((char *)GetScriptClass(object) + 0x24) = argument;
}
