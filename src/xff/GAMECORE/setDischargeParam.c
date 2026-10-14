typedef int s128 __attribute__((mode(TI)));
union DischargeVector {
    s128 q;
    float f[4];
};

extern int getSpecialEffectObjWork(void *effect);

void setDischargeParam(void *effect, union DischargeVector *vector, float first, float second)
{
    void *work = (void *)getSpecialEffectObjWork(effect);

    *(float *)work = first;
    *(float *)((char *)work + 4) = second;
    ((union DischargeVector *)((char *)effect + 0x20))->q = vector->q;
}
