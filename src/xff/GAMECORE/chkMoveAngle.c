int chkMoveAngle(float angle, float target) {
    int result;

    result = 1;
    if (!(fabsf(angle + target) <= 1.7453293e-02f) && (((target >= 0.0f) && (angle >= 0.0f)) || ((result = 0, (target <= 0.0f)) && (angle <= 0.0f)))) {
        result = 1;
        if (!(fabsf(angle) >= fabsf(target))) {
            result = 0;
        }
    }
    return result;
}
