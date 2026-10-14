int CAM_is_reach_aim_pitch(float *out, int dir, float start, float unused, float pitch, float aim)
{
    int reached = 0;

    if (start == aim || pitch == aim) {
        pitch = aim;
        reached = 1;
    } else if (dir == 1) {
        if (aim < pitch) {
            pitch = aim;
            reached = 1;
        }
    } else if (dir == -1) {
        if (pitch < aim) {
            pitch = aim;
            reached = 1;
        }
    }
    if (out != 0) {
        *out = pitch;
    }
    return reached;
}
