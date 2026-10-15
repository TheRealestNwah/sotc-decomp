extern void GetEulerYXZFromQuaternion(void *, void *);
extern void GetEulerZXYFromQuaternion(void *, void *);

void convert_from_quater_to_rotXYZ_direct_motion_ik_base(void *rot, void *q, int mode)
{
    switch (mode) {
    case 0:
        GetEulerYXZFromQuaternion(rot, q);
        return;
    case 1:
        GetEulerZXYFromQuaternion(rot, q);
        return;
    default:
        __asm__ __volatile__("break 0");
    }
}
