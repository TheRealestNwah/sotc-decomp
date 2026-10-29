extern int Sg2ExStAdpcmSlotReserv(int, int);
int Sg2ExStAdpcmSlotMalloc(int count)
{
    return Sg2ExStAdpcmSlotReserv(0, count);
}
