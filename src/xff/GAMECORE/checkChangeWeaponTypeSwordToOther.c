extern void fadeout_weakpoint_effect(void);
extern void cancel_fadeout_weakpoint_effect(void);

void checkChangeWeaponTypeSwordToOther(int prev, int next)
{
    if (next == prev) {
        return;
    }
    if (prev < 4) {
        if (prev > 0) {
            if (next < 4) {
                if (next > 0) {
                    return;
                }
            }
            fadeout_weakpoint_effect();
            return;
        }
    }
    if (next < 4) {
        if (next > 0) {
            cancel_fadeout_weakpoint_effect();
        }
    }
}
