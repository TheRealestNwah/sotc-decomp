typedef int s128 __attribute__((mode(TI)));
extern s128 D_0017B340;
extern s128 D_0017B350;
extern int D_0017B360;

void sprWeaponSetMarker(s128 *a, s128 *b, int c)
{
    if (c != 0 && a != 0) {
        D_0017B340 = *a;
        D_0017B350 = *b;
    }
    D_0017B360 = c;
}
