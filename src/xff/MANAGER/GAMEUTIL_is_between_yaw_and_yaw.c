/* Returns whether yaw lies between yaw0 and yaw1, taking the short way around
   the circle: when the two bounds are more than PI apart the result inverts. */
int GAMEUTIL_is_between_yaw_and_yaw(float yaw, float yaw0, float yaw1)
{
    float diff = yaw0 - yaw1;
    int wrap = 0;

    /* The shared label reproduces the original branch layout. */
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
