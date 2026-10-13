extern void iosSetSyncNoReturnFunc(void *);
extern unsigned char func_0007A930[1];

void SetVIF1MarkCallbackFunc(void)
{
    iosSetSyncNoReturnFunc(&func_0007A930);
}
