int GetMotionResourceRotAngle(int kind)
{
    int angle = 0;

    switch (kind) {
    case 0:
        break;
    case 1:
    case 3:
        angle = 0x4000;
        break;
    case 2:
        angle = -0x4000;
        break;
    }
    return angle;
}
