static inline int is_nearly_zero(float x, float eps)
{
    if (x < 0.0f) {
        if (-x <= eps) {
            goto yes;
        } else {
            goto no;
        }
    } else {
        if (x <= eps) {
            goto yes;
        } else {
            goto no;
        }
    }
yes:
    return 1;
no:
    return 0;
}
typedef int Quad __attribute__((mode(TI)));
extern Quad ZUnitVector;
extern void iosRotMatrixX(float *, float);
extern void iosApplyRotMatrix(void *, void *, void *);
void GAMEUTIL_get_pitch_dir(Quad *out, float pitch)
{
    float matrix[16] __attribute__((aligned(16)));
    if (is_nearly_zero(pitch, 0.0001f) == 1) {
        *out = ZUnitVector;
    } else {
        if (pitch > 1.483529806137085f) {
            pitch = 1.483529806137085f;
        }
        else if (pitch < -1.483529806137085f) {
            pitch = -1.483529806137085f;
        }
        iosRotMatrixX(matrix, -pitch);
        iosApplyRotMatrix(out, matrix, &ZUnitVector);
    }
}

