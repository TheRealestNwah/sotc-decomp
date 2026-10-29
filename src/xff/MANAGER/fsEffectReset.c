extern void skipBlur(int);
extern int solarFlareReset();

int fsEffectReset(void)
{
    skipBlur(1);
    return solarFlareReset();
}
