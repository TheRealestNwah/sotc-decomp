static int chkCurveCollision(void *, float);
float adjustCurveAngleForCollision(void *actor, float angle, float threshold, float distance)
{
    if (threshold < __builtin_fabsf(angle)) {
        int status = chkCurveCollision(actor, distance);
        if (status != 2) {
            if (status == 3 && angle < 0.0f)
                angle += 6.28318500518798828125f;
        } else {
            if (0.0f < angle)
                angle += -6.28318500518798828125f;
        }
    }
    return angle;
}
