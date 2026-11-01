typedef struct {
    float decay;
    float add;
    float addBig;
    int flag;
} AngryParam;

typedef struct {
    AngryParam *p;
    float val;
} AngryWork;

extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern int *GetDamageClass(void *);

void updateAngryWork(void *obj)
{
    AngryWork *w = (AngryWork *)(getSCRDataCtrlWork(obj) + 0x40F4);

    if (w->p) {
        int *dc = GetDamageClass(obj);
        int state = dc[0];
        int kind = dc[0x60 / 4];
        if (state == 3) {
            if (kind == 0 || kind == 5)
                w->val += w->p->addBig;
            else if (kind == 1 || kind == 4 || kind == 2 || (w->p->flag && kind == 3))
                w->val += w->p->add;
        } else {
            w->val -= w->p->decay * *(float *)(gcGlobalVar + 0x190);
        }
    }
    w->val = (100.0f <= w->val) ? 100.0f : w->val;
    w->val = (w->val <= 0.0f) ? 0.0f : w->val;
}
