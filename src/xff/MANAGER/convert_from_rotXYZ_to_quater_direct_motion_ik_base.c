extern void GetQuaternionByEulerYXZ(float *, float, float, float);
extern void GetQuaternionByEulerZXY(float *, float, float, float);

void convert_from_rotXYZ_to_quater_direct_motion_ik_base(float *q, float *r, int order)
{
    switch (order) {
    case 0:
        GetQuaternionByEulerYXZ(q, r[0], r[1], r[2]);
        break;
    case 1:
        GetQuaternionByEulerZXY(q, r[0], r[1], r[2]);
        break;
    default:
        __asm__ __volatile__("break 0");
        break;
    }
}
