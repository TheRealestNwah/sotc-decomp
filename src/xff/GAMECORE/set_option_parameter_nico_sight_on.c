extern void set_pitch_parameter_effective_ratio_nico_yaw_pitch_cntrl(void *, float);
extern void set_reverse_input_pitch_flag_nico_yaw_pitch_cntrl(void *, int);
extern void set_reverse_input_yaw_flag_nico_yaw_pitch_cntrl(void *, int);
extern void set_yaw_parameter_effective_ratio_nico_yaw_pitch_cntrl(void *, float);

void set_option_parameter_nico_sight_on(void *work, int yaw, int pitch, float ratio)
{
    void *control;

    control = (char *)work + 0xC;
    set_reverse_input_yaw_flag_nico_yaw_pitch_cntrl(control, yaw);
    set_reverse_input_pitch_flag_nico_yaw_pitch_cntrl(control, pitch);
    set_yaw_parameter_effective_ratio_nico_yaw_pitch_cntrl(control, ratio);
    set_pitch_parameter_effective_ratio_nico_yaw_pitch_cntrl(control, ratio);
}
