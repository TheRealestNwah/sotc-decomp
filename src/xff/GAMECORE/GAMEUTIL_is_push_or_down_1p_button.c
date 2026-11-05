extern struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
} padManagerData;

#ifdef NONMATCHING
int GAMEUTIL_is_push_or_down_1p_button(int kind, int bit)
{
    int mask;
    int v;

    if (kind == 1) {
        mask = 1 << bit;
        v = padManagerData.x8;
    } else if (kind == 2) {
        mask = 1 << bit;
        v = padManagerData.xC;
    } else if (kind == 3) {
        mask = 1 << bit;
        v = padManagerData.x10;
    } else {
        if (!(padManagerData.x0 & (1 << bit))) {
            return 0;
        }
        return 1;
    }
    if (!(v & mask)) {
        return 0;
    }
    return 1;
}
#endif
