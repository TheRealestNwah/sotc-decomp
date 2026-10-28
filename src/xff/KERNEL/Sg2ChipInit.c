extern void Sg2CtrlSetTickTime(int);
extern void Sg2RemoteSend(int, int, int, int);

int Sg2ChipInit(int reserved)
{
    Sg2CtrlSetTickTime(0);
    Sg2RemoteSend(0x11, 0, 0, 0);
    return 0;
}
