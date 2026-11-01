typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V4;
extern int isysGetThisSubThread(void);
extern void scrRun(void);
extern char *GetScriptClass(int);
extern char *GetLayoutClass(int);
extern int GetWaterSurfacePositionY(void *, float *, void *, float, float);
extern void SetGeometryPointerNodePosState(void *, int, int, void *, void *);
extern int _SCRSetupLWS(int, void *, void *, void *, int);
extern void _SCRStartLWS(int, int, int, int);
extern void isysRequestDeleteObj(int);
extern V4 IdentityQuaternion;
extern V4 ZeroPoint;
extern char gcGlobalVar[];

static void func_0003F488(int arg)
{
    char gp[0x40];
    float wy;
    int lws = 0;
    int th = isysGetThisSubThread();

    scrRun();
    while (1) {
        int obj = *(int *)(GetScriptClass(th) + 0x2C);
        float *pos = *(float **)(GetLayoutClass(obj) + 0x134);
        if (GetWaterSurfacePositionY(&wy, pos, gcGlobalVar + 0x230, pos[1] + 100.0f, pos[1])) {
            if (lws != 0) {
                isysRequestDeleteObj(lws);
                lws = 0;
            }
        } else if (lws == 0) {
            SetGeometryPointerNodePosState(gp, obj, 0, &IdentityQuaternion, &ZeroPoint);
            lws = _SCRSetupLWS(arg, gp, &ZeroPoint, &IdentityQuaternion, th);
            if (lws != 0)
                _SCRStartLWS(lws, -1, 5, 0);
        }
        scrRun();
    }
}
