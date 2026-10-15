extern int iosSetSyncNoReturnFunc(void (*func)(unsigned int vif1Stat));
extern void func_0007A930(unsigned int vif1Stat);

void SetVIF1MarkCallbackFunc(void)
{
    iosSetSyncNoReturnFunc(&func_0007A930);
}
