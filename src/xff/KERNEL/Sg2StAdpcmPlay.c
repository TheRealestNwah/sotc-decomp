extern int Sg2RemoteSend(int, int, int, int);

int Sg2StAdpcmPlay(unsigned long id)
{
    if (id != 0)
        Sg2RemoteSend(0x1C, id & 0xFFFFFF, (id >> 24) & 0xFFFFFF, 0);
    return 0;
}
