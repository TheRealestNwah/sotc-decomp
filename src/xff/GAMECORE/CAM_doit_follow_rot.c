extern float func_000E22C0(char *, float);
extern float func_000E22E0(char *, void *, float);
extern float func_000E2308(char *, void *, float);
extern float func_000E2330(void *, void *);
extern void func_000DF090(char *, void *, float);
extern void func_000DF200(char *, void *, void *, float);

void CAM_doit_follow_rot(char *c, void *b, void *d, float t)
{
    *(float *)(c + 0x1A0) = func_000E22C0(c, t);
    *(float *)(c + 0x1A4) = func_000E22E0(c, d, t);
    *(float *)(c + 0x1A8) = func_000E2308(c, b, t);
    *(float *)(c + 0x1AC) = func_000E2330(b, d);
    func_000DF090(c, b, t);
    func_000DF200(c, b, d, t);
}
