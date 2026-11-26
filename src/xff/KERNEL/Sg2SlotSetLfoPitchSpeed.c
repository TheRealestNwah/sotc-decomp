#include "kernel/sg2slot.h"

#ifdef NONMATCHING
/* Parked: 2 words differ (base materialized via lui $v1 instead of lui $v0/addiu $v1) */
void Sg2SlotSetLfoPitchSpeed(int slot, int speed)
{
    int off = ({ register int s7 __asm__("$5") = slot * 7; __asm__("" : "+r"(s7)); s7 << 5; });
    register int offc __asm__("$9") = off;
    register int o70 __asm__("$7");
    __asm__("" : "+r"(offc));
    o70 = offc + 0x70;
    __asm__("" : "+r"(o70));
    if (speed != 0) {
        speed = 0xF0 / (0x3C - speed * 58 / 127);
    }
    {
        register char *base __asm__("$3") = (char *)B_000DE370;
        register char *bc __asm__("$4") = base;
        register Sg2Slot *fe __asm__("$5");
        register int *lp __asm__("$8");
        __asm__("" : "+r"(bc));
        fe = (Sg2Slot *)(off + base);
        lp = (int *)(bc + o70);
        __asm__("" : "+r"(lp));
        {
            register int *l2 __asm__("$2") = lp;
            register int *l3 __asm__("$3");
            __asm__("" : "+r"(l2));
            l3 = l2;
            __asm__("" : "+r"(l3));
            l2[2] = speed;
            l3[4] = 0;
            if (speed != 0 && lp[3] != 0) {
                register Sg2Slot *fs __asm__("$3") = (Sg2Slot *)(offc + (int)bc);
                fs->flags |= 0x400;
                return;
            }
        }
        fe->flags &= ~0x400;
    }
}
#endif
