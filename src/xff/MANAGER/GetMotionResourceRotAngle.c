int GetMotionResourceRotAngle(int type)
{
    int angle = 0;

    switch (type) {
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
