extern float iosGetSecondFromTCount(unsigned long);
extern long iosGetTCountExtension(void);
extern float D_00137724;
void mouseDispCursor(void)
{
    D_00137724 = iosGetSecondFromTCount((unsigned long)iosGetTCountExtension());
}