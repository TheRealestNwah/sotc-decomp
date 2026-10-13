extern int SCRGetFirstObj(void *);
extern void SaveLayoutObjGroupAllGeo();
extern void func_00018E00(int, int);
extern int stagemanager_getSegmentVariation();
extern unsigned char gcGlobalVar[1];

void gStatCheckPointSave(void)
{
    int temp_s0;
    int temp_s1;

    temp_s0 = stagemanager_getSegmentVariation();
    temp_s1 = SCRGetFirstObj(&gcGlobalVar + 0x2B4);
    SaveLayoutObjGroupAllGeo();
    func_00018E00(temp_s0, temp_s1 != 0);
}
