extern int D_0017B040;
extern void func_000BC988(int);

void playerlifebar_effect(int type)
{
    do {
        func_000BC988(4);
    } while (0);
    switch (type) {
    case 0:
        D_0017B040 |= 1;
        break;
    case 1:
        D_0017B040 |= 2;
        break;
    }
}
