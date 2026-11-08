extern void GetEulerYXZFromQuaternion(float *euler, void *quat);

void GetEulerYXZFromQuaternionZHalfPI(float *euler, void *quat)
{
    float z;

    GetEulerYXZFromQuaternion(euler, quat);
    z = euler[2];
    if (z < 0.0f) {
        if (!(z < -1.5707963f)) {
            return;
        }
    } else if (!(1.5707963f < z)) {
        return;
    }
    if (euler[1] < 0.0f) {
        euler[1] = euler[1] + 3.1415926f;
    } else {
        euler[1] = euler[1] - 3.1415926f;
    }
    if (0.0f < euler[0]) {
        euler[0] = 3.1415926f - euler[0];
    } else {
        euler[0] = -3.1415926f - euler[0];
    }
    if (0.0f < z) {
        euler[2] = z - 3.1415926f;
    } else {
        euler[2] = z + 3.1415926f;
    }
}
