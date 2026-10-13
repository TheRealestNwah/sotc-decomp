extern void FlushLayoutObj();
extern void *GetScriptLayoutClass(int);
extern void flushScriptObj(int);
extern void iosFree(int);

void FlushScriptLayoutObj(int arg0)
{
    int temp_v1;

    FlushLayoutObj();
    flushScriptObj(arg0);
    temp_v1 = (*(int *)((char *)(GetScriptLayoutClass(arg0)) + 0x2D4));
    if (temp_v1 != 0) {
        iosFree(temp_v1);
    }
}
