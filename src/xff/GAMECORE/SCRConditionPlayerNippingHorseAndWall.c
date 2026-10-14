extern void *getSCRDataCtrlWork(void *);
extern int nico_playerCheckNippingWithHorseAndWall(int);

int SCRConditionPlayerNippingHorseAndWall(void *actor)
{
    return nico_playerCheckNippingWithHorseAndWall((*(int *)((char *)(getSCRDataCtrlWork(actor)) + 0x4078))) != 0;
}
