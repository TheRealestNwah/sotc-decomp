int GetMotionResourceRotAngle(int axis)
{
    int angle = 0;

    switch (axis) {
    case 1:
    case 3:
        angle = 0x4000;
        break;
    case 2:
        angle = -0x4000;
        break;
    default:
        break;
    case 0:
        break;
    }
    return angle;
}
