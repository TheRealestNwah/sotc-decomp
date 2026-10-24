extern int FlushLayoutObj(unsigned char *);
extern void *GetScriptLayoutClass(unsigned char *);
extern void flushScriptObj(int);
extern void iosFree(int);

void FlushScriptLayoutObj(unsigned char *object)
{
    int allocation;

    FlushLayoutObj(object);
    flushScriptObj((int)object);
    allocation = *(int *)((char *)GetScriptLayoutClass(object) + 0x2D4);
    if (allocation != 0) {
        iosFree(allocation);
    }
}
