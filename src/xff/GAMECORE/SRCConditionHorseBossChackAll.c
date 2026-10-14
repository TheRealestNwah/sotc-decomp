extern char gcGlobalVar[];
extern int SCRGetFirstObj();

int SRCConditionHorseBossChackAll(void)
{
    return SCRGetFirstObj(gcGlobalVar + 0x2B8) != 0;
}
