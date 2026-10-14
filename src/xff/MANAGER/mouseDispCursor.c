extern float iosGetSecondFromTCount(int);
extern int iosGetTCountExtension();
extern float D_00137724;

void mouseDispCursor(void)
{
    D_00137724 = iosGetSecondFromTCount(iosGetTCountExtension());
}
