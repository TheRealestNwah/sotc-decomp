typedef struct { char p0[0x168]; float f168; int p16C; float f170; char p174[0x228-0x174]; char vu[0x10]; } GV;
extern GV gcGlobalVar;
extern void initVuColiDispWork(void *);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void doit_debug_utility(float);
extern void disp_debug_utility(void);
extern void updateVuColiDispWork(void);
extern void dispVuColiDispWork(void);
extern void drawGazeTool(float);
extern void scrRun(void);

static void func_00008050(void)
{


    initVuColiDispWork(gcGlobalVar.vu);
    for (;;) {
        iosDlPushLayer(0x18);
        doit_debug_utility(gcGlobalVar.f170);
        disp_debug_utility();
        updateVuColiDispWork();
        dispVuColiDispWork();
        drawGazeTool(gcGlobalVar.f168);
        iosDlPopLayer();
        scrRun();
    }
}
