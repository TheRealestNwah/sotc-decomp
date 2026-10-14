extern void iosRotMatrixY(void *, float);
extern void iosApplyRotMatrix(void *, void *, void *);
extern char ZUnitVector[];

void GAMEUTIL_get_direction_by_yaw(void *out, float yaw)
{
    float m[16] __attribute__((aligned(16)));
    iosRotMatrixY(m, yaw);
    iosApplyRotMatrix(out, m, ZUnitVector);
}
