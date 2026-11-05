typedef int s128 __attribute__((mode(TI)));
typedef struct {
    long v[6];
} CamFinBase;

extern char gcGlobalVar[];
extern s128 ZeroPoint;
extern CamFinBase D_00179FB0;
extern int D_00179FA0;
extern int D_00179FE0;
extern char *iosgluGetCameraContext(void);
extern void scrRun(void);

void st_camfinalizer(void)
{
    char *a;
    char *b;

    *(CamFinBase *)(gcGlobalVar + 0x340) = D_00179FB0;
    *(s128 *)(gcGlobalVar + 0x370) = ZeroPoint;
    D_00179FA0 = 0;
    while (1) {
        *(s128 *)(gcGlobalVar + 0x350) = *(s128 *)(gcGlobalVar + 0x340);
        if (D_00179FE0 == 0) {
            a = iosgluGetCameraContext();
            b = iosgluGetCameraContext();
            *(s128 *)(gcGlobalVar + 0x340) = *(s128 *)(a + 0x140);
            *(s128 *)(gcGlobalVar + 0x360) = *(s128 *)(b + 0x150);
        }
        *(s128 *)(gcGlobalVar + 0x370) = *(s128 *)(iosgluGetCameraContext() + 0x140);
        scrRun();
    }
}
