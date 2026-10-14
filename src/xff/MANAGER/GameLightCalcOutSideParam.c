void GameLightCalcOutSideParam(void *arg0)
{
    float temp_f0;

    temp_f0 = (*(float *)((char *)(arg0) + 0x28));
    (*(float *)((char *)(arg0) + 0x34)) = (float) (temp_f0 * temp_f0);
}
