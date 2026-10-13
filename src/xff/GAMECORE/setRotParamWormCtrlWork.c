typedef struct {
    char pad0[0x6C];
    float f6C;
    float f70;
} WormCtrl;

void setRotParamWormCtrlWork(WormCtrl *w, float a, float deg)
{
    w->f6C = a;
    w->f70 = deg * 0.0174532925f;
}
