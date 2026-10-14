extern int skipBlur();
extern int solarFlareReset();

int fsEffectReset(void)
{
    skipBlur(1);
    return solarFlareReset();
}
