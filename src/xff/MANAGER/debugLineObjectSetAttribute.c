extern void iosDlChainTailCurrent(void *);
extern int D_00135C58;

void debugLineObjectSetAttribute(int arg0)
{
    if ((D_00135C58 == -1) || (arg0 != D_00135C58)) {
        if (arg0 != -1) {
            iosDlChainTailCurrent((void *)arg0);
        }
        D_00135C58 = arg0;
    }
}
