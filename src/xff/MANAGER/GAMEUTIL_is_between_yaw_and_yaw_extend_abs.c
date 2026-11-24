static inline int between_yaw(float yaw, float yaw0, float yaw1)
{
    float diff = yaw0 - yaw1;
    int wrap = 0;

    if (diff < 0.0f) {
        if (diff < -3.1415926f) {
            goto wrapped;
        }
    } else if (diff > 3.1415926f) {
    wrapped:
        wrap = 1;
    }
    if ((yaw0 <= yaw && yaw <= yaw1) || (yaw1 <= yaw && yaw <= yaw0)) {
        if (wrap) {
            return 0;
        }
        return 1;
    }
    if (wrap) {
        return 1;
    }
    return 0;
}

int GAMEUTIL_is_between_yaw_and_yaw_extend_abs(float yaw, float base, float yaw1, float yaw2)
{
    if (between_yaw(yaw, base, yaw1) == 1 || between_yaw(yaw, base, yaw2) == 1) {
        return 1;
    }
    return 0;
}
