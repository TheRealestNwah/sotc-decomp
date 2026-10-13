extern void iosJumpRecoverPoint(void *, int, int, int);
extern unsigned char RO_00041E80[1];

void _iosAssert(int arg0, int arg1, int arg2)
{
    iosJumpRecoverPoint(&RO_00041E80, arg0, arg1, arg2);
}
