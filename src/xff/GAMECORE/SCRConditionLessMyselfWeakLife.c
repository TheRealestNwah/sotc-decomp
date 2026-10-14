extern float getBossWeakLifeRatio(void *, int);
int SCRConditionLessMyselfWeakLife(void *actor, int b, int c, int d, int e, int index, float threshold)
{
    return getBossWeakLifeRatio(actor, index) * 100.0f <= threshold;
}
