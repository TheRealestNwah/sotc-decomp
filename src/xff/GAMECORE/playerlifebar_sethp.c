typedef struct {
    float cur;
    float prev;
    float target;
    float speed;
} LifeBar;

extern LifeBar D_0017B030;
extern int D_0017B040;
extern void func_000BC988(int);

void playerlifebar_sethp(float hp)
{
    if (hp == D_0017B030.cur)
        return;
    D_0017B030.prev = D_0017B030.target;
    if (hp < D_0017B030.cur) {
        func_000BC988(4);
        D_0017B030.cur = hp;
        D_0017B040 |= 1;
    } else {
        D_0017B030.cur = hp;
        D_0017B030.target = hp;
    }
    D_0017B030.speed = 0.1f;
    func_000BC988(1);
}
