extern long *GetCollisionDBAttributeAdr();

int coliJudgeNotWater(void)
{
    return (*GetCollisionDBAttributeAdr() & 0x7C00) != 0x4400;
}
