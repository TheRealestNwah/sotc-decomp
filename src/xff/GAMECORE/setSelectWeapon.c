extern void CancelSwordEffect(int);
extern volatile int D_0017B330;
extern int D_0017B334;
extern void setWeaponSpriteStatus(int, int);

void setSelectWeapon(int w)
{
    int old;
    CancelSwordEffect(w);
    old = D_0017B330;
    D_0017B330 = w;
    D_0017B334 = old;
    setWeaponSpriteStatus(w, old);
}
