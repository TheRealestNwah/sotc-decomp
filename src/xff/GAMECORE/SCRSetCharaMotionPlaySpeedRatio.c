extern void MotSpdCtrl_SetSpeed(void *, int);
extern unsigned char B_0018A660[];

void SCRSetCharaMotionPlaySpeedRatio(int arg0)
{
    MotSpdCtrl_SetSpeed(B_0018A660, arg0);
}
