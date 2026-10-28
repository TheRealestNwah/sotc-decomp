typedef struct FollowRotationParameter {
    int unknown00[2];
    float ratio;
    float duration;
} FollowRotationParameter;
typedef struct CameraParameters {
    unsigned char unknown0000[0x2D20];
    FollowRotationParameter *mode2;
    unsigned char unknown2D24[0x2DE0 - 0x2D24];
    FollowRotationParameter *mode3;
    unsigned char unknown2DE4[0x2ED0 - 0x2DE4];
    FollowRotationParameter *mode4;
    unsigned char unknown2ED4[0x2FF0 - 0x2ED4];
    FollowRotationParameter *mode5;
    unsigned char unknown2FF4[0x3120 - 0x2FF4];
    FollowRotationParameter *mode6;
} CameraParameters;
extern void GAMEUTIL_reset_interp_ratio_cntrl(void *);
extern void GAMEUTIL_set_param_interp_ratio_cntrl(void *, float, float);

void CAM_reset_mode_ratio_follow_rot(char *control, int mode, CameraParameters *parameters)
{
    float ratio = 0.0f;
    float duration = 1.0f;
    switch (mode) {
    case 2:
        ratio = parameters->mode2->ratio;
        duration = parameters->mode2->duration;
        break;
    case 3:
        ratio = parameters->mode3->ratio;
        duration = parameters->mode3->duration;
        break;
    case 4:
        ratio = parameters->mode4->ratio;
        duration = parameters->mode4->duration;
        break;
    case 5:
        ratio = parameters->mode5->ratio;
        duration = parameters->mode5->duration;
        break;
    case 6:
        ratio = parameters->mode6->ratio;
        duration = parameters->mode6->duration;
        break;
    default:
        goto apply;
    }
apply:
    if (duration < 0.1f)
        duration = 0.1f;
    {
        char *ratioControl = control + 0x20;
        GAMEUTIL_reset_interp_ratio_cntrl(ratioControl);
        GAMEUTIL_set_param_interp_ratio_cntrl(ratioControl, ratio, duration);
    }
}
