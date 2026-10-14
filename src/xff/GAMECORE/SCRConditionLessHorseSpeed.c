extern void *SCRGetFirstObj(void *);
extern float getHorseInterpSpeed(void *);
extern unsigned char gcGlobalVar[];

int SCRConditionLessHorseSpeed(float speed)
{
    void *horse = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    int result;

    if (horse == 0) {
        return 0;
    }
    result = 1;
    if (!(getHorseInterpSpeed(horse) <= speed)) {
        result = 0;
    }
    return result;
}
