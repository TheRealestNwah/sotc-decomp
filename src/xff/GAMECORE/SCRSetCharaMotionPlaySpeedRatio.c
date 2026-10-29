extern int MotSpdCtrl_SetSpeed(void *, void *, float);
extern unsigned char B_0018A660[];

void SCRSetCharaMotionPlaySpeedRatio(void *actor, float speed)
{
    MotSpdCtrl_SetSpeed(B_0018A660, actor, speed);
}
