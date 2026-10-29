extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);

int SRCConditionHorseBossChackAll(void)
{
    return SCRGetFirstObj(gcGlobalVar + 0x2B8) != 0;
}
