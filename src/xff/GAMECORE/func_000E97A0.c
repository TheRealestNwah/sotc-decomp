extern void func_000E9900(char *, int, void *);
extern void func_000ED330(char *);
extern float get_view_angle_camera_view_angle_cntrl(void *);
extern float GetGameTimeScaleRatio(void);
extern void CAM_set_all_camera_base_data(void *, void *, void *, float, float, float);
extern void CAM_shuffle_lws_base_space_target_boss_interest_axis_X(void);
extern void setDemoBar(float, float);
extern void gameModeSet(int);
extern void gameModeCls(int);
extern void *CAM_get_target_obj(void *);
extern void CharaCtrlResetPlayableCtrlStatus(void *);
extern void nico_playerSetAttentionHeadActFlag(void *, int);

#define I(o) (*(int *)(a + (o)))

static void func_000E97A0(char *a, char *b, void *c)
{
    void *p60 = b + 0x60;
    float va;

    I(0x8C) = 0;
    I(0x98) = 0;
    func_000E9900(a, I(0x90), c);
    I(0x100) = 0;
    *(float *)(a + 0x104) = -1.0f;
    va = get_view_angle_camera_view_angle_cntrl(b + 0x1C8);
    CAM_set_all_camera_base_data(a + 0x110, p60, b + 0x70, *(float *)(b + 0x1C0), va,
                                 GetGameTimeScaleRatio());
    CAM_shuffle_lws_base_space_target_boss_interest_axis_X();
    if (I(0xA0) != 0)
        setDemoBar(1.0f, 2.0f);
    else
        setDemoBar(0.0f, 2.0f);
    func_000ED330(a);
    if (I(0xC4) == 1) {
        gameModeSet(1);
        CharaCtrlResetPlayableCtrlStatus(CAM_get_target_obj(b + 0x23C));
        I(0x80)++;
    } else if (I(0x80) > 0) {
        gameModeCls(1);
        I(0x80)--;
    }
    nico_playerSetAttentionHeadActFlag(CAM_get_target_obj(b + 0x23C), I(0xC8));
    I(0x84) = 1;
}
