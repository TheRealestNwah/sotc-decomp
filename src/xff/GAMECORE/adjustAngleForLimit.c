float adjustAngleForLimit(float angle, float limit)
{
    if (limit < angle) {
        return limit;
    }
    if (angle < -limit) {
        return -limit;
    }
    return angle;
}
