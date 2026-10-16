extern int D_0017B330;
extern float *ScrParam_bow_range;
extern float *ScrParam_harpoon_range;
extern float getPlayerMaxGripRatio(void);

float GetWeaponRange(void)
{
    switch (D_0017B330) {
    case 1:
    case 2:
    case 3:
        return 500.0f;
    case 4:
    case 6:
    case 7:
        return getPlayerMaxGripRatio() * ScrParam_bow_range[1];
    case 5:
        return ScrParam_harpoon_range[1];
    }
    return 0.0f;
}
