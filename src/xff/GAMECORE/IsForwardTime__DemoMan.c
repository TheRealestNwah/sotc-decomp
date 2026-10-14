extern void *GetScriptLayoutClass(void *context);

int IsForwardTime__DemoMan(void *context, float time)
{
    void *work = *(void **)((char *)GetScriptLayoutClass(context) + 0x2D8);

    if (*(int *)((char *)work + 0x2C) <= 0) {
        goto yes;
    }
    if (!(*(float *)((char *)work + 0x34) <= time)) {
        goto no;
    }
    if (!(time <= *(float *)((char *)work + 0x40))) {
        goto no;
    }

yes:
    return 1;
no:
    return 0;
}
