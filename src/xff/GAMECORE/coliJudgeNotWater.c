extern long *GetCollisionDBAttributeAdr(void *);

int coliJudgeNotWater(void *collision)
{
    return (*GetCollisionDBAttributeAdr(collision) & 0x7C00) != 0x4400;
}
