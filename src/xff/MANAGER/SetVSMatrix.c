typedef struct {
    char pad0[8];
    float far;
    float near;
    float vs10;
    float vs14;
    float vs18;
} ViewScreen;

extern void func_000E4F38(ViewScreen *);

void SetVSMatrix(ViewScreen *vs)
{
    vs->vs10 = vs->near;
    vs->vs14 = 1.0f;
    vs->vs18 = vs->far;
    func_000E4F38(vs);
}
