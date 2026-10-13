extern float iosGetRandom();
extern int D_0017B680;

void CAM_shuffle_lws_base_space_target_boss_interest_axis_X(void)
{
    if (iosGetRandom() < 0.5f) {
        D_0017B680 = 1;
        return;
    }
    D_0017B680 = 0;
}
