typedef struct {
    int state;
    char pad4[0x18];
    float time;
} WeaponSprite;

typedef struct {
    char pad0[0x178];
    float time;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern WeaponSprite B_0019CD48[];
extern int D_0017B044;
extern int D_0017B048;
extern void func_000BC988(int);

static inline void setState(int i, int st)
{
    B_0019CD48[i].state = st;
    B_0019CD48[i].time = gcGlobalVar.time;
}

void setWeaponSpriteStatus(int cur, int next)
{
    int c = cur - 1;

    D_0017B044 = c;
    D_0017B048 = next - 1;
    if (B_0019CD48[c].state != 2)
        setState(c, 1);
    if (D_0017B048 != D_0017B044 && B_0019CD48[D_0017B048].state != 0)
        setState(D_0017B048, 3);
    func_000BC988(2);
}
