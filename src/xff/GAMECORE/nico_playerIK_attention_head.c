typedef int s128 __attribute__((mode(TI)));
extern int func_0007DC80(void *);
extern char *GetSCRCharaAIWorkPtr(void *);
extern int func_0007ABA0(s128 *, char *, void *);
extern void begin_motion_ik_interest(void *);
extern void request_end_motion_ik_interest(void *);
extern void doit_motion_ik_interest(void *, void *, s128 *, float);
extern s128 ZeroPoint;
extern char gcGlobalVar[];

void nico_playerIK_attention_head(void **arg)
{
    void *obj = *arg;
    int mode = func_0007DC80(obj);
    char *w = GetSCRCharaAIWorkPtr(obj);
    s128 v;
    if (mode == 1 && func_0007ABA0(&v, w, obj) == 1) {
        begin_motion_ik_interest(w + 0x4C0);
    } else {
        request_end_motion_ik_interest(w + 0x4C0);
        v = ZeroPoint;
    }
    doit_motion_ik_interest(w + 0x4C0, arg, &v, *(float *)(gcGlobalVar + 0x180));
}

void nico_playerIK_attention_chest(void **arg)
{
    void *obj = *arg;
    int mode = func_0007DC80(obj);
    char *w = GetSCRCharaAIWorkPtr(obj);
    s128 v;
    if (mode == 2 && func_0007ABA0(&v, w, obj) == 1) {
        begin_motion_ik_interest(w + 0x550);
    } else {
        request_end_motion_ik_interest(w + 0x550);
        v = ZeroPoint;
    }
    doit_motion_ik_interest(w + 0x550, arg, &v, *(float *)(gcGlobalVar + 0x180));
}
