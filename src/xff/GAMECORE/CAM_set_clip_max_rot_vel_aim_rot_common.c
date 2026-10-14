void CAM_set_clip_max_rot_vel_aim_rot_common(char *p, float f)
{
    *(float *)(p + 0xC) = f * 0.0174532925f;
}
