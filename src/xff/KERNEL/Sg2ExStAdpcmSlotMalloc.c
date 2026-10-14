extern int Sg2ExStAdpcmSlotReserv();

int Sg2ExStAdpcmSlotMalloc(int a, int b, int c, int d)
{
    return Sg2ExStAdpcmSlotReserv(0, a, c, d);
}
