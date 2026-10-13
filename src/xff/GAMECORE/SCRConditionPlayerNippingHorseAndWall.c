extern void *getSCRDataCtrlWork();
extern int nico_playerCheckNippingWithHorseAndWall(int);

int SCRConditionPlayerNippingHorseAndWall(void)
{
    return nico_playerCheckNippingWithHorseAndWall((*(int *)((char *)(getSCRDataCtrlWork()) + 0x4078))) != 0;
}
