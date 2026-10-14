extern void *GetSCRCharaAIWorkPtr(void *);

int SRCConditionHorseAngleFromPlayerToHorse(void *actor, float lower, float upper)
{
    float angle;
    int result;
    int selected;

    angle = *(float *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x4234);
    result = 0;
    selected = 0;
    if (angle != -1.0f) {
        result = 0;
        if (lower * 0.0174532925f <= angle) {
            if (angle <= upper * 0.0174532925f) {
                selected = 1;
            }
        }
        result = selected;
    }
    return result;
}
