typedef struct {
    int x0;
    char pad4[8];
    int xC;
    int x10;
} CamEtcCondition;

extern void func_000D7CC8(CamEtcCondition *c);

static void func_000D7CA0(CamEtcCondition *c)
{
    c->x0 = 0;
    c->xC = 0;
    c->x10 = 0;
    func_000D7CC8(c);
}
