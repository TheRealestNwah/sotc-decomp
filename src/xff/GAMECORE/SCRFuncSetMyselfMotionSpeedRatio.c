extern void SCRSetCharaMotionPlaySpeedRatio(void *, float);

void SCRFuncSetMyselfMotionSpeedRatio(void *actor, float speed)
{
    SCRSetCharaMotionPlaySpeedRatio(actor, speed);
}
