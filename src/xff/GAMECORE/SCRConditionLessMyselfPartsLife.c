extern float getBossPartsLifeRatio(void *, int);
int SCRConditionLessMyselfPartsLife(void *actor, int b, int c, int d, int e, int index, float threshold)
{
    return getBossPartsLifeRatio(actor, index) * 100.0f <= threshold;
}
