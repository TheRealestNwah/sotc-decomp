extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, float *);
extern void SetQuaternionByAxisRotateV(void *, short, float *);
void GetQuaternionAxisRot(float *out, float *axis, int mode, float angle)
{
    if (mode) {
        SetQuaternionByAxisRotateVWithNoRegularize(out, -(int)((angle * 32768.0f) / 3.1415926f), axis);
    } else {
        SetQuaternionByAxisRotateV(out, -(int)((angle * 32768.0f) / 3.1415926f), axis);
    }
}
