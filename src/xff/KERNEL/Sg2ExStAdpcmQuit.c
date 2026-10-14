extern void Sg2ExStAdpcmSlotFree();
extern void Sg2StAdpcmQuit();

void Sg2ExStAdpcmQuit(void)
{
    Sg2ExStAdpcmSlotFree();
    Sg2StAdpcmQuit();
}
