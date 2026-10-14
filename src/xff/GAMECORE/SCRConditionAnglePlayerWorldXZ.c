extern void *getSCRDataCtrlWork(void *);
extern float fabsf(float);

int SCRConditionAnglePlayerWorldXZ(void *actor, float limit)
{
    int result;

    result = 1;
    if (!(fabsf(*(float *)((char *)getSCRDataCtrlWork(actor) + 0x4068))
          <= limit * 0.0174532925f)) {
        result = 0;
    }
    return result;
}
